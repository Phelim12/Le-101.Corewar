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

t_header	fill_header(t_line **file)
{
	t_header	result;
	t_cmd		*line;
	int			count;

	count = 0;
	line = (*file)->line;
	while (count++ < 2)
	{
		if (!(ft_strcmp(line->data, NAME_CMD_STRING)))
		{
			line = line->next;
			if (line && line->type && ft_strlen(line->data) < PROG_NAME_LENGTH)
				ft_strncpy(result.prog_name, line->data, PROG_NAME_LENGTH);
			else
				print_error_reader((*file), line->pos);
		}
		else if (!(ft_strcmp(line->data, COMMENT_CMD_STRING)))
		{
			line = line->next;
			if (line && line->type && ft_strlen(line->data) < COMMENT_LENGTH)
				ft_strncpy(result.comment, line->data, COMMENT_LENGTH);
			else
				print_error_reader((*file), line->pos);
		}
		else
			print_error_reader((*file), line->pos);
		if (line->next)
			print_error_reader((*file), line->next->pos);
		free_line(line);
		(*file) = (*file)->next;
		free((*file)->prev);
		line = (*file)->line;
	}
	(*file)->start = (*file);
	while ((line = line->next))
		line->start = line->prev->start;
	return (result);
}

int		main(int argc, char const *argv[])
{
	t_file	info;
	int		fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (0);
		if ((info.file = reader(NULL, NULL, fd)))
		{
			info.header = fill_header(&(info.file));
		}
		else
			ft_putendl_fd(ERROR_MSG_01, 2);
		print_file(info.file);
		// printf("print_label\n");
		// print_label(info.file, NULL);
		free_file(info.file);
		close(fd);
	}
	return (0);
}
