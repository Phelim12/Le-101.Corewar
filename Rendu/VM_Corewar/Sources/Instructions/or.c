/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   or.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:12:23 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 22:19:01 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		or_reg(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->registers[(*proc)->params[0][1]] |
			(*proc)->registers[(*proc)->params[1][1]];
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->registers[(*proc)->params[0][1]] |
			(*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			| (*proc)->params[1][1];
	}
}

void		or_dir(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->params[0][1] |
			(*proc)->registers[(*proc)->params[1][1]];
	}
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			(*proc)->params[0][1] |
			(*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[1][1] % IDX_MOD, 4)
			| (*proc)->params[0][1];
	}
}

void		or_ind(t_process **proc)
{
	if ((*proc)->params[1][0] == 1)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			| (*proc)->registers[(*proc)->params[1][1]];
	}
	else if ((*proc)->params[1][0] == 2)
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4)
			| (*proc)->params[1][1];
	}
	else
	{
		(*proc)->registers[(*proc)->params[2][1]] =
			read_map((*proc)->begin + (*proc)->params[1][1] % IDX_MOD, 4)
			| read_map((*proc)->begin + (*proc)->params[0][1] % IDX_MOD, 4);
	}
}

void		ft_or(t_process **proc)
{
	if ((*proc)->params[0][0] == 1)
		or_reg(proc);
	else if ((*proc)->params[0][0] == 2)
		or_dir(proc);
	else
		or_ind(proc);
	(*proc)->carry = (!(*proc)->registers[(*proc)->params[2][1]] ? 1 : 0);
}
