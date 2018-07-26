/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   and.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:17:36 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 22:20:58 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		and_reg(t_process **proc)
{
	if (PROC->params[1][0] == REG_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->reg[PROC->params[0][1]] &
			PROC->reg[PROC->params[1][1]]);
	if (PROC->params[1][0] == DIR_CODE)
		PROC->reg[PROC->params[2][1]] =
			(PROC->reg[PROC->params[0][1]] & PROC->params[1][1]);
	if (PROC->params[1][0] == IND_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->params[1][1] &
			read_map(PROC->begin + PROC->params[0][1] % IDX_MOD));
}

void		and_dir(t_process **proc)
{
	if (PROC->params[1][0] == REG_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->params[0][1] &
			PROC->reg[PROC->params[1][1]]);
	if (PROC->params[1][0] == DIR_CODE)
		PROC->reg[PROC->params[2][1]] = 
			(PROC->params[0][1] & PROC->params[1][1]);
	if (PROC->params[1][0] == IND_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->params[0][1] &
			read_map(PROC->begin + PROC->params[1][1] % IDX_MOD));
}

void		and_ind(t_process **proc)
{
	if (PROC->params[1][0] == REG_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->reg[PROC->params[1][1]] &
			read_map(PROC->begin + PROC->params[0][1] % IDX_MOD));
	if (PROC->params[1][0] == DIR_CODE)
		PROC->reg[PROC->params[2][1]] = (PROC->params[1][1] &
			read_map(PROC->begin + PROC->params[0][1] % IDX_MOD));
	if (PROC->params[1][0] == IND_CODE)
		PROC->reg[PROC->params[2][1]] =
			(read_map(PROC->begin + PROC->params[1][1] % IDX_MOD) &
				read_map(PROC->begin + PROC->params[0][1] % IDX_MOD));
}

void		ft_and(t_process **proc)
{
	if (PROC->params[0][0] == REG_CODE)
		and_reg(proc);
	if (PROC->params[0][0] == DIR_CODE)
		and_dir(proc);
	if (PROC->params[0][0] == IND_CODE)
		and_ind(proc);
	PROC->carry = (!PROC->reg[PROC->params[2][1]] ? 1 : 0);
}
