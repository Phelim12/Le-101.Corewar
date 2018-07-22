/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:49:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 16:49:10 by nbettach    ###    #+. /#+    ###.fr     */
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

int		error_vm(char *s, int c)
{
	unsigned int i;

	i = 0;
	if (!ft_strcmp("open", s))
		ft_printf("Can't read source file %s\n", g_vm->champion[c]->filename);
	else if (!ft_strcmp("size", s))
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
		g_vm->champion[c]->filename, g_vm->champion[c]->prog_size,
		MEM_SIZE / 6);
	else
		ft_printf(s);
	free_all();
	exit(1);
	return (-1);
}
