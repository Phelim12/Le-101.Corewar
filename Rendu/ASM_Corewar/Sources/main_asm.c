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
