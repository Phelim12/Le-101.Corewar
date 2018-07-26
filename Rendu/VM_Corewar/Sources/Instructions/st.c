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

void		ft_st(t_process **proc)
{
	unsigned char	*tab;
	int				aim;
	int				i;

	i = -1;
	tab = NULL;
	aim = (PROC->begin + PROC->params[1][1] % IDX_MOD) % MEM_SIZE;
	if (aim < 0)
		aim += MEM_SIZE;
	if (PROC->params[1][0] == 1)
		PROC->reg[PROC->params[1][1]] = PROC->reg[PROC->params[0][1]];
	else
	{
		tab = itoo(PROC->reg[PROC->params[0][1]]);
		while (++i < 4)
			print(PROC->reg[1], (aim + i) % MEM_SIZE, tab[i]);
	}
}
