/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:49:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 07:42:00 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void	print_usage(void)
{
	ft_printf(USE1);
	ft_printf(USE2);
	ft_printf(USE3);
}

void	print_error_read(int var)
{
	ft_putstr_fd("Can't read source file ", 2);
	ft_putendl_fd(g_vm->champion[var]->filename, 2);
}

void	print_error_size(int var)
{
	ft_putstr_fd("Error: File ", 2);
	ft_putstr_fd(g_vm->champion[var]->filename, 2);
	ft_putstr_fd(" has too large a code (", 2);
	ft_putnbr_fd(g_vm->champion[var]->prog_size, 2);
	ft_putstr_fd(" bytes > ", 2);
	ft_putnbr_fd((MEM_SIZE / 6), 2);
	ft_putendl_fd(" bytes)", 2);
}

void	error_vm(char *str, int var)
{
//	if (!(ft_strcmp("open", str)))
//		print_error_read(var);
//	 if (!(ft_strcmp("size", str)))
//		print_error_size(var);
//	else if (str)
//		ft_putstr_fd(str, 2);
//	else
	free_all();
	exit(1);
}
