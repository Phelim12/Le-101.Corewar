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

void		ft_lld(t_process **proc)
{
	int aim;

	aim = PROC->begin + PROC->params[0][1];
	if (PROC->params[0][0] == DIR_CODE)
		PROC->reg[PROC->params[1][1]] = PROC->params[0][1];
	if (PROC->params[0][0] == IND_CODE)
		PROC->reg[PROC->params[1][1]] = read_map(aim);
	PROC->carry = (!PROC->reg[PROC->params[1][1]] ? 1 : 0);
}
