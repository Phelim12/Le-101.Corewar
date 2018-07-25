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

char	*find_file(char const *argv[])
{
	char	*tmp;
	int 	var;

	var = -1;
	while (argv[++var])
	{
		tmp = ft_strrchr(argv[var], '.');
		if (tmp && !(ft_strcmp(tmp, ".s")))
			return ((char *)argv[var]);
	}
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(": No \".s\" file in paramters" , 2);
	exit(EXIT_FAILURE);
	return (0);
}

int 	check_verbose(char const *argv[])
{
	int var;

	var = -1;
	while (argv[++var])
		if (!(ft_strcmp("-v", argv[var])))
			return (1);
	return (0);
}

int		main(int argc, char const *argv[])
{
	t_file	info;
	char	*str;
	int		fd;

	str = find_file(argv);
	if ((fd = open(str, O_RDONLY)) == -1)
		file_not_exist(str);
	if ((info.file = parser(NULL, fd))->line->token != END)
	{
		info.header = parser_header(&(info.file), 1, 1);
		parser_label(info.file);
		parser_code(info.file);
		close(fd);
	}
	else
		print_error_token(info.file, info.file->line, SYNTAX_MSG);
	if (check_verbose(argv))
		verbose_file(info);
	write_file(info, str);
	free_file(info.file);
	return (0);
}
