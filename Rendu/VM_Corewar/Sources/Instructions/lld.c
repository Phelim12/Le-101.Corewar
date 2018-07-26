/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lld.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 13:59:30 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:22:07 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_lld(t_process **proc)
{
	dprintf(1, "register[%d] = %d\n",
			PROC->params[1][1],
			PROC->reg[PROC->params[1][1]]);
}

void		ft_lld(t_process **proc)
{
	int aim;

	aim = PROC->begin + PROC->params[0][1];
	if (PROC->params[0][0] == 2)
		PROC->reg[PROC->params[1][1]] =
			PROC->params[0][1];
	else
		PROC->reg[PROC->params[1][1]] =
			read_map(aim, REG_SIZE);
	PROC->carry = (!PROC->reg[PROC->params[1][1]] ? 1 : 0);
//	debug_lld(proc);
}
