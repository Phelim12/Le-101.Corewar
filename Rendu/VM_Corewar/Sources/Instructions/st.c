/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   st.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:03 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:22:17 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_st(t_process **proc, int aim)
{
	dprintf(2, "PC = %d\n", PROC->reg[0]);
	dprintf(2, "aim = %d\n", aim);
	dprintf(2, "params : %d & %d\n",
			PROC->params[0][1],
			PROC->params[1][1]);
	dprintf(2, "register[%d] = %d\n",
			PROC->params[0][1],
			PROC->reg[PROC->params[0][1]]);
}

void		ft_st(t_process **proc)
{
	int				aim;
	unsigned char	*tab;
	int				i;

	i = -1;
	tab = NULL;
	aim = (PROC->begin + PROC->params[1][1] % IDX_MOD) % MEM_SIZE;
	if (aim < 0)
		aim += MEM_SIZE;
//	debug_st(proc, aim);
	if (PROC->params[1][0] == 1)
		PROC->reg[PROC->params[1][1]] =
			PROC->reg[PROC->params[0][1]];
	else
	{
		tab = itoo(PROC->reg[PROC->params[0][1]]);
		while (++i < 4)
			print(PROC->reg[1], (aim + i) % MEM_SIZE, tab[i]);
	}
}
