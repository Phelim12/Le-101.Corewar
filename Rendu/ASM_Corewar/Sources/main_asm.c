/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:54:45 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 15:15:30 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	file_not_exist(char const *argv[])
{
	ft_putstr_fd(argv[0] + 2, 2);
	ft_putstr_fd(": ", 2);
	perror(argv[1]);
	exit(EXIT_FAILURE);
}

void	cant_create_file(char const *argv[], char *name_exec, t_file info)
{
	ft_putstr_fd(argv[0], 2);
	perror(name_exec);
	free_file(info.file);
	exit(EXIT_FAILURE);
}

void	convert_integer(unsigned char **ptr ,int n)
{
	(*ptr)[0] = (n >> 24) & 0xFF;
	(*ptr)[1] = (n >> 16) & 0xFF;
	(*ptr)[2] = (n >> 8) & 0xFF;
	(*ptr)[3] = n & 0xFF;
}

void	convert_short(unsigned char **ptr ,int n)
{
	(*ptr)[0] = (n >> 8) & 0xFF;
	(*ptr)[1] = n & 0xFF;
}

void	write_binary_int(int fd, int nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_integer(&str, nb);
	write(fd, str, 4);
	free(str);
}

void	write_binary_short(int fd, short nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(2);
	convert_short(&str, nb);
	write(fd, str, 2);
	free(str);
}

char	*name_exec_file(const char *name)
{
	char	*result;
	char	*str;

	result = ft_strnew(ft_strlen(name) + 5);
	ft_strcat(result, name);
	if ((str = ft_strrchr(result, '.')))
	{
		str[1] = 'c';
		str[2] = 'o';
		str[3] = 'r';
	}
	else
		ft_strcat(result, ".cor");
	return (result);
}

void	write_register(t_cmd *ptr, int fd)
{
	char	nb_reg;

	nb_reg = (char)ft_atoi(ptr->data + 1);
	write(fd, &(nb_reg), 1);
}

int		label_byte(t_label *label, char *label_name)
{
	t_label *tmp;

	tmp = label;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, label_name)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	write_indirect(t_line *tmp, t_cmd *ptr, int fd)
{
	short	label_value;
	short	nb_ind;

	if (ptr->token == INDIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data);
		write_binary_short(fd, nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 1));
		nb_ind = label_value - (short)tmp->size;
		if (nb_ind > 0 && nb_ind < ptr->start->octet)
			write_binary_short(fd, ptr->start->octet);
		else
			write_binary_short(fd, nb_ind);
	}
}

void	write_direct_short(t_line *tmp, t_cmd *ptr, int fd)
{
	short	label_value;
	short	nb_ind;

	if (ptr->token == DIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data + 1);
		write_binary_short(fd, nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - (short)tmp->size;
		if (nb_ind > 0 && nb_ind < ptr->start->octet)
			write_binary_short(fd, ptr->start->octet);
		else
			write_binary_short(fd, nb_ind);
	}
}

void	write_direct_int(t_line *tmp, t_cmd *ptr, int fd)
{
	int	label_value;
	int	nb_ind;

	if (ptr->token == DIRECT)
	{
		nb_ind = ft_atoi(ptr->data + 1);
		write_binary_int(fd, nb_ind);
	}
	else
	{
		label_value = label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - tmp->size;
		if (nb_ind > 0 && nb_ind < ptr->start->octet)
			write_binary_short(fd, ptr->start->octet);
		else
			write_binary_short(fd, nb_ind);
	}
}

void	write_instruction(t_line *tmp, t_cmd *cmds, int fd)
{
	t_cmd	*ptr;
	t_op	info;

	ptr = cmds->next;
	info = instruction_exist(cmds->data);
	write(fd, &(info.opcode), 1);
	if (info.info_params)
		write(fd, &(cmds->info), 1);
	while (ptr)
	{
		if (ptr->token == REGISTER)
			write_register(ptr, fd);
		if (ptr->token == DIRECT_LABEL || ptr->token == DIRECT)
		{
			if (info.size_dir)
				write_direct_short(tmp, ptr, fd);
			else
				write_direct_int(tmp, ptr, fd);
		}
		if (ptr->token == INDIRECT_LABEL || ptr->token == INDIRECT)
			write_indirect(tmp, ptr, fd);
		ptr = ptr->next;
	}
}

void		write_code(t_line *file, int fd)
{
	t_line	*tmp;
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line;
		while (ptr)
		{
			if (ptr->token == INSTRUCTION)
				write_instruction(tmp, ptr, fd);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

void	write_header(t_header header, int fd)
{
	write_binary_int(fd, header.magic);
	write(fd, header.name, NAME_LENGTH);
	write_binary_int(fd, 0);
	write_binary_int(fd, header.prog_size);
	write(fd, header.comment, COMMENT_LENGTH);
	write_binary_int(fd, 0);
}

void	write_file(t_file info, char const *argv[])
{
	char			*name_exec;
	int				fd;

	name_exec = name_exec_file(argv[1]);
	if ((fd = open(name_exec, O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1)
		cant_create_file(argv, name_exec, info);
	write_header(info.header, fd);
	write_code(info.file, fd);
	ft_putstr("Writing output program to ");
	ft_putendl(name_exec);
	ft_strdel(&name_exec);
	close(fd);
}

void		parser_code(t_line *file)
{
	t_line	*tmp;
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line;
		while (ptr)
		{
			if ((ptr->token == END && ptr->prev) ||
				(ptr->token == COMMAND_NAME || ptr->token == COMMAND_COMMENT))
				print_error_token(file, ptr, SYNTAX_MSG);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

int		main(int argc, char const *argv[])
{
	t_file	info;
	int		fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			file_not_exist(argv);
		if ((info.file = parser(NULL, fd))->line->token != END)
		{
			info.header = parser_header(&(info.file), 1, 1);
			parser_label(info.file);
			parser_code(info.file);
			close(fd);
		}
		else
			print_error_token(info.file, info.file->line, SYNTAX_MSG);

		write_file(info, argv);
		free_file(info.file);
	}
	return (0);
}
// 0d90 0000 0007 10
// 0d90 ffff fff9 10 