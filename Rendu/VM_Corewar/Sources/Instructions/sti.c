/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 14:47:18 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_sti(t_process **proc, int aim, int debug)
{
	if (debug == 1)
	{
		dprintf(2, "sti PC = %d\n", (*proc)->registers[0]);
		dprintf(2, "sti params : %d & %d\n",
				(*proc)->fetchqueue[0][1], (*proc)->fetchqueue[1][1]);
		dprintf(2, "sti register[%d] = %d\n",
				(*proc)->fetchqueue[0][1],
				(*proc)->registers[(*proc)->fetchqueue[0][1]]);
	}
	else if (debug == 2)
	{
		dprintf(2, "sti aim = %d\n", aim);
		dprintf(1, "register[%d] = %d\n",
				(*proc)->fetchqueue[0][1],
				(*proc)->registers[(*proc)->fetchqueue[0][1]]);
	}
}

void		ft_sti(t_process **proc)
{
	int				fparam;
	int				sparam;
	int				aim;
	unsigned char	*tab;
	int				i;

	debug_sti(proc, 0, 1);
	i = -1;
	tab = NULL;
	if ((*proc)->fetchqueue[1][0] == 3)
		fparam =
			read_map((*proc)->fetchqueue[1][1] % IDX_MOD + (*proc)->begin, 4);
	else if ((*proc)->fetchqueue[1][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	else
		fparam = (*proc)->fetchqueue[1][1];
	if ((*proc)->fetchqueue[2][0] == 1)
		sparam = (*proc)->registers[(*proc)->fetchqueue[2][1]];
	else
		sparam = (*proc)->fetchqueue[2][1];
	aim = (fparam + sparam) % IDX_MOD + (*proc)->begin;
	tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
	while (++i < 4)
		print((*proc)->registers[1], aim + i, tab[i]);
	debug_sti(proc, aim, 2);
}
