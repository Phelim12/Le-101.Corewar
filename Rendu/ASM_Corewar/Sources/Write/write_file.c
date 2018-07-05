/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:14:37 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 16:14:37 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

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

void	write_code(t_line *file, int fd)
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
				write_params(tmp, ptr, fd);
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
	char	*name_exec;
	int		fd;

	name_exec = name_exec_file(argv[1]);
	if ((fd = open(name_exec, O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1)
		cant_create_file(argv, name_exec, info);
	write_header(info.header, fd);
	write_code(info.file, fd);
	ft_printf(MSG_WRITING, name_exec);
	ft_strdel(&name_exec);
	close(fd);
}
