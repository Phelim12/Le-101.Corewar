/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ld.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:25:29 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:21:32 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_ld(t_process **proc, int aim)
{
	dprintf(1, "AIM = %d\n", aim);
	dprintf(1, "register[%d] = %d\n",
			(*proc)->fetchqueue[1][1],
			(*proc)->registers[(*proc)->fetchqueue[1][1]]);
}

void		ft_ld(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
	if ((*proc)->fetchqueue[0][0] == 2)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			(*proc)->fetchqueue[0][1];
	else
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			read_map(aim, REG_SIZE);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[1][1]] ? 1 : 0);
//	debug_ld(proc, aim);
}
