/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ldi.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:27:04 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 14:43:23 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_ldi(t_process **proc)
{
	dprintf(1, "register[%d] = %d\n",
			(*proc)->fetchqueue[2][1],
			(*proc)->registers[(*proc)->fetchqueue[2][1]]);
}

void		ft_ldi(t_process **proc)
{
	int		fparam;
	int		sparam;

	if ((*proc)->fetchqueue[0][0] == 3)
		fparam =
			read_map(((*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD), 4);
	else if ((*proc)->fetchqueue[0][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[0][1]];
	else
		fparam = (*proc)->fetchqueue[0][1];
	if ((*proc)->fetchqueue[1][0] == 2)
		sparam = (*proc)->fetchqueue[1][1];
	else
		sparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = read_map(((fparam + sparam)
			% IDX_MOD + (*proc)->begin), 4);
	debug_ldi(proc);
}
