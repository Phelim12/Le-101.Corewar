/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sub.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:10:14 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:22:43 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_sub(t_process **proc)
{
	dprintf(1, "1st param (%d) + 2nd param (%d) = %d\n",
			PROC->reg[PROC->params[0][1]],
			PROC->reg[PROC->params[1][1]],
			PROC->reg[PROC->params[2][1]]);
}

void		ft_sub(t_process **proc)
{
	PROC->reg[PROC->params[2][1]] =
		PROC->reg[PROC->params[0][1]] -
		PROC->reg[PROC->params[1][1]];
	PROC->carry = (!PROC->reg[PROC->params[2][1]] ? 1 : 0);
//	debug_sub(proc);
}
