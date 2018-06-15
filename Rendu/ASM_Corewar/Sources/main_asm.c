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
			return (0);
		if ((info.file = reader(NULL, NULL, fd)))
		{
			// info.header = fill_header(info.file);
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
