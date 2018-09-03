/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:20:11 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 18:52:18 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int		ft_dump(void)
{
	unsigned int	i;
	
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("%-#5.4x : ", i);
		else if (i % (g_vm->d_size ? g_vm->d_size : 32) == 0)
			ft_printf("\n%-#5.4x : ", i);
		ft_printf("%02x", g_vm->map[i]);
		ft_printf(" ");
	}
	ft_printf("\n");
	return (0);
}
