/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zjmp.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:02:02 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 22:36:02 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_zjmp(t_process **proc)
{
	dprintf(2, "begin zjmp aim = %d\nparam = %d\n",
			((*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD) % MEM_SIZE,
			(*proc)->fetchqueue[0][1]);
	dprintf(2, "end zjmp aim = %d\n", (*proc)->registers[0]);
}

void		ft_zjmp(t_process **proc)
{
	// dprintf(2, "CARRY = %d\n", (*proc)->carry);
	int jump;

	jump = (*proc)->fetchqueue[0][1] % IDX_MOD;
	if ((*proc)->carry == 1)
	{
		(*proc)->registers[0] = ((*proc)->begin + jump) % MEM_SIZE;
		if ((*proc)->registers[0] < 0)
		{
			(*proc)->registers[0] += MEM_SIZE;
		}
	}
	// debug_zjmp(proc);
}

/*
P2 |	zjmp	0		PC -> 10		Cycle 230

CARRY = 1
begin zjmp aim = 10
param = 0
end zjmp aim = 10

P1 |	add	r4, r12, r4		PC -> 169		Cycle 239

P2 |	live	-1		PC -> 13		Cycle 243

P1 |	sub	r10, r11, r10		PC -> 174		Cycle 249

P2 |	sti	r15, %0, r14		PC -> 18		Cycle 268

P1 |	zjmp	-50		PC -> 179		Cycle 269

CARRY = 0
begin zjmp aim = 129
param = -50
end zjmp aim = 182

P2 |	zjmp	-200		PC -> 24		Cycle 288

CARRY = 1
begin zjmp aim = -176
param = -200
end zjmp aim = 3920*/