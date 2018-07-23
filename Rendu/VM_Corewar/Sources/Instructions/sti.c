/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 18:38:16 by jjanin-r    ###    #+. /#+    ###.fr     */
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
				(*proc)->fetchqueue[1][1], (*proc)->fetchqueue[2][1]);
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

//	debug_sti(proc, 0, 1);
	i = -1;
	tab = NULL;
	/*while (++i < 3)
	{
		dprintf(2, "params type = %d | value = %d\n", (*proc)->fetchqueue[i][0], (*proc)->fetchqueue[i][1]);
		dprintf(2, "register %d value = %d\n", i, (*proc)->registers[(*proc)->fetchqueue[i][1]]);
	}*/
	if ((*proc)->fetchqueue[1][0] == 3)
		fparam = read_map(((*proc)->fetchqueue[1][1] < 0 ?
			(*proc)->fetchqueue[1][1] + MEM_SIZE :
				(*proc)->fetchqueue[1][1]) % IDX_MOD + (*proc)->begin, 4);
	else if ((*proc)->fetchqueue[1][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	else if ((*proc)->fetchqueue[1][0] == 2)
		fparam = (*proc)->fetchqueue[1][1];
	if ((*proc)->fetchqueue[2][0] == 1)
		sparam = (*proc)->registers[(*proc)->fetchqueue[2][1]];
	else
		sparam = (*proc)->fetchqueue[2][1];
	aim = (fparam + sparam) % IDX_MOD + (*proc)->begin;
	tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
	i = -1;
	while (++i < 4)
		print((*proc)->registers[1], aim + i, tab[i]);
//	debug_sti(proc, aim, 2);
}
