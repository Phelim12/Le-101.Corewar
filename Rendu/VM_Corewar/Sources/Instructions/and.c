/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   and.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:17:36 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 15:23:50 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_and(t_process **proc)
{
	dprintf(2, "OPCODE = %d\n", (*proc)->op);
	dprintf(1, "1st param (%d) & 2nd param (%d) = %d\n",
			(*proc)->fetchqueue[0][1],
			(*proc)->fetchqueue[1][1],
			(*proc)->registers[(*proc)->fetchqueue[2][1]]);
}

void		and_reg(t_process **proc)
{
	if ((*proc)->fetchqueue[1][0] == 1)
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			(*proc)->registers[(*proc)->fetchqueue[0][1]] &
			(*proc)->registers[(*proc)->fetchqueue[1][1]];
	else if ((*proc)->fetchqueue[1][0] == 2)
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			(*proc)->registers[(*proc)->fetchqueue[0][1]] &
			(*proc)->fetchqueue[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4)
			& (*proc)->fetchqueue[1][1];
	}
}

void		and_dir(t_process **proc)
{
	if ((*proc)->fetchqueue[1][0] == 1)
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			(*proc)->fetchqueue[0][1] &
			(*proc)->registers[(*proc)->fetchqueue[1][1]];
	}
	else if ((*proc)->fetchqueue[1][0] == 2)
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			(*proc)->fetchqueue[0][1] &
			(*proc)->fetchqueue[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4)
			& (*proc)->fetchqueue[0][1];
	}
}

void		and_ind(t_process **proc)
{
	if ((*proc)->fetchqueue[1][0] == 1)
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4)
			& (*proc)->registers[(*proc)->fetchqueue[1][1]];
	}
	else if ((*proc)->fetchqueue[1][0] == 2)
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4)
			& (*proc)->fetchqueue[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4)
			& read_map(((*proc)->begin + (*proc)->fetchqueue[0][1])
					% IDX_MOD, 4);
	}
}

void		ft_and(t_process **proc)
{
	if ((*proc)->fetchqueue[0][0] == 1)
		and_reg(proc);
	else if ((*proc)->fetchqueue[0][0] == 2)
		and_dir(proc);
	else
		and_ind(proc);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
	debug_and(proc);
}
