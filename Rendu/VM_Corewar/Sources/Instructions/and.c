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

void		debug_and(t_process **proc)
{
	dprintf(2, "OPCODE = %d\n", (*proc)->op);
	dprintf(1, "1st param (%d) & 2nd param (%d) = %d\n",
			(*proc)->params[0][1],
			(*proc)->params[1][1],
			(*proc)->registers[(*proc)->params[2][1]]);
}

void		and_reg(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->registers[(*proc)->params[0][1]] &
			(*proc)->registers[(*proc)->params[1][1]];
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->registers[(*proc)->params[0][1]] &
			(*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			& (*proc)->params[1][1];
	}
}

void		and_dir(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->params[0][1] &
			(*proc)->registers[(*proc)->params[1][1]];
	}
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->params[0][1] &
			(*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[1][1] % IDX_MOD, 4)
			& (*proc)->params[0][1];
	}
}

void		and_ind(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			& (*proc)->registers[(*proc)->params[1][1]];
//	dprintf(2, "%d + %d", read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4), (*proc)->registers[(*proc)->params[1][1]]);
	}
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			& (*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[1][1] % IDX_MOD, 4)
			& read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4);
	}
}

void		ft_and(t_process **proc)
{
	if ((*proc)->params[0][0] == 1)
		and_reg(proc);
	else if ((*proc)->params[0][0] == 2)
		and_dir(proc);
	else
		and_ind(proc);
	(*proc)->carry = (!(*proc)->registers[(*proc)->params[2][1]] ? 1 : 0);
//	debug_and(proc);
}
