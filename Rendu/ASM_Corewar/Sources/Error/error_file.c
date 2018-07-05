/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 20:25:01 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 20:25:01 by clcreuso    ###    #+. /#+    ###.fr     */
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
