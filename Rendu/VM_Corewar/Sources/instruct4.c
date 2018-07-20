/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct4.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:06:55 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 13:41:17 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_xor(t_process **proc)
{
	if ((*proc)->fetchqueue[0][0] == 1)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] ^
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] ^
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) ^
				(*proc)->fetchqueue[1][1];
		}
	}
	else if ((*proc)->fetchqueue[0][0] == 2)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] ^
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] ^
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) ^
				(*proc)->fetchqueue[0][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) ^
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else if ((*proc)->fetchqueue[1][0] == 2)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4) ^
				(*proc)->fetchqueue[1][1];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				read_map(((*proc)->begin + (*proc)->fetchqueue[1][1]) % IDX_MOD, 4) ^
				read_map(((*proc)->begin + (*proc)->fetchqueue[0][1]) % IDX_MOD, 4);
		}
	}
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
}

int				check_registers(t_process *proc)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] < 2)
			return (0);
	return (1);
}
