/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ldi.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:27:04 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:21:40 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_ldi(t_process **proc)
{
	int		fparam;
	int		sparam;

	fparam	= 0;
	sparam	= 0;
	if (PROC->params[0][0] == REG_CODE)
		fparam = PROC->reg[PROC->params[0][1]];
	if (PROC->params[0][0] == DIR_CODE)
		fparam = PROC->params[0][1];
	if (PROC->params[0][0] == IND_CODE)
		fparam = read_map((PROC->begin + PROC->params[0][1] % IDX_MOD));
	if (PROC->params[1][0] == DIR_CODE)
		sparam = PROC->params[1][1];
	if (PROC->params[1][0] == REG_CODE)
		sparam = PROC->reg[PROC->params[1][1]];
	PROC->reg[PROC->params[2][1]] = read_map((fparam + sparam)
			% IDX_MOD + PROC->begin);
}
