/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   st.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:03 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:56:50 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_st(t_process **proc, int aim)
{
	dprintf(2, "PC = %d\n", (*proc)->registers[0]);
	dprintf(2, "aim = %d\n", aim);
	dprintf(2, "params : %d & %d\n",
			(*proc)->fetchqueue[0][1],
			(*proc)->fetchqueue[1][1]);
	dprintf(2, "register[%d] = %d\n",
			(*proc)->fetchqueue[0][1],
			(*proc)->registers[(*proc)->fetchqueue[0][1]]);
}

void		ft_st(t_process **proc)
{
	int				aim;
	unsigned char	*tab;
	int				i;

	i = -1;
	tab = NULL;
	aim = ((*proc)->begin + (*proc)->fetchqueue[1][1] % IDX_MOD) % MEM_SIZE;
	if (aim < 0)
		aim += MEM_SIZE;
//	debug_st(proc, aim);
	if ((*proc)->fetchqueue[1][0] == 1)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			(*proc)->registers[(*proc)->fetchqueue[0][1]];
	else
	{
		tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
		while (++i < 4)
			print((*proc)->registers[1], aim + i, tab[i]);
	}
}
