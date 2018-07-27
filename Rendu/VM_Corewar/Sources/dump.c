/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:20:11 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 02:09:12 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int		print_color(int i, int *p, int pc)
{
	if (!(p[0] == g_vm->p_map[i] || p[1] == g_vm->p_map[i] ||
				p[2] == g_vm->p_map[i] || p[3] == g_vm->p_map[i]))
	{
		if (!p[0])
			p[0] = g_vm->p_map[i];
		else if (!p[1])
			p[1] = g_vm->p_map[i];
		else if (!p[2])
			p[2] = g_vm->p_map[i];
		else if (!p[3])
			p[3] = g_vm->p_map[i];
	}
	if (g_vm->p_map[i] == p[0])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[1])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[2])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[3])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	return (0);
}

int		ft_dump(void)
{
	unsigned int	i;
	int				p[4];

	i = -1;
	while (++i < g_vm->nb_players)
		p[i] = i;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("%-#5.4x : ", i);
		else if (i % (g_vm->d_size ? g_vm->d_size : 64) == 0)
			ft_printf("\n%-#5.4x : ", i);
		ft_printf("%02x", g_vm->map[i]);
		ft_printf(" ");
	}
	ft_printf("\n");
	return (0);
}
