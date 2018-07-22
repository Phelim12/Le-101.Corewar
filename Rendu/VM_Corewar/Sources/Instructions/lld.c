/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lld.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 13:59:30 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 14:13:59 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_lld(t_process **proc)
{
	dprintf(1, "register[%d] = %d\n",
			(*proc)->fetchqueue[1][1],
			(*proc)->registers[(*proc)->fetchqueue[1][1]]);
}

void		ft_lld(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
	if ((*proc)->fetchqueue[0][0] == 2)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			(*proc)->fetchqueue[0][1];
	else
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			read_map(aim, REG_SIZE);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[1][1]] ? 1 : 0);
	debug_lld(proc);
}
