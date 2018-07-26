/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ld.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:25:29 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 02:18:07 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_ld(t_process **proc)
{
	int aim;

	aim = PROC->begin + PROC->params[0][1] % IDX_MOD;
	if (PROC->params[0][0] == DIR_CODE)
		PROC->reg[PROC->params[1][1]] = PROC->params[0][1];
	if (PROC->params[0][0] == IND_CODE)
		PROC->reg[PROC->params[1][1]] = read_map(aim);
	PROC->carry = (!PROC->reg[PROC->params[1][1]] ? 1 : 0);
}
