/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct3.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:02:59 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 12:47:04 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_lfork(t_process **proc, t_process **begin)
{
	int				aim;
	t_process		*new;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
//	dprintf(1, "aim = %d\n", aim);
	new = lstnew_vm((*proc)->registers, REG_SIZE * REG_NUMBER);
	new->registers[0] = aim;
	lstadd_vm(begin, new);
}

void		ft_add(t_process **proc)
{
	(*proc)->registers[(*proc)->fetchqueue[2][1]] =
		((*proc)->registers[(*proc)->fetchqueue[0][1]] +
		 (*proc)->registers[(*proc)->fetchqueue[1][1]]);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
//	dprintf(1, "1st param (%d) + 2nd param (%d) = %d\n",
//			(*proc)->registers[(*proc)->fetchqueue[0][1]],
//			(*proc)->registers[(*proc)->fetchqueue[1][1]],
//			(*proc)->registers[(*proc)->fetchqueue[2][1]]);
}

void		ft_sub(t_process **proc)
{
	
	(*proc)->registers[(*proc)->fetchqueue[2][1]] =
		(*proc)->registers[(*proc)->fetchqueue[0][1]] -
		(*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
//	dprintf(1, "1st param (%d) - 2nd param (%d) = %d\n",
//			(*proc)->registers[(*proc)->fetchqueue[0][1]],
//			(*proc)->registers[(*proc)->fetchqueue[1][1]],
//			(*proc)->registers[(*proc)->fetchqueue[2][1]]);
}

void		ft_or(t_process **proc)
{
	if ((*proc)->fetchqueue[0][0] == 1)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] |
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] |
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) |
				(*proc)->fetchqueue[1][1];
		}
	}
	else if ((*proc)->fetchqueue[0][0] == 2)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] |
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] |
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) |
				(*proc)->fetchqueue[0][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) |
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) |
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) |
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4);
		}
	}
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
}

void		ft_and(t_process **proc)
{
	//dprintf(2, "OPCODE = %d\n", (*proc)->op);
	if ((*proc)->fetchqueue[0][0] == 1)
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
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) &
				(*proc)->fetchqueue[1][1];
		}
	}
	else if ((*proc)->fetchqueue[0][0] == 2)
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
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) &
				(*proc)->fetchqueue[0][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) &
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) &
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) &
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4);
		}
	}
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
//	dprintf(1, "1st param (%d) & 2nd param (%d) = %d\n",
//			(*proc)->fetchqueue[0][1],
//			(*proc)->fetchqueue[1][1],
//			(*proc)->registers[(*proc)->fetchqueue[2][1]]);
}
