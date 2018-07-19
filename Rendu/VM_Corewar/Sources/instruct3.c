/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct3.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:02:59 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 15:29:01 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_lfork(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
	//creer une copie du process a g_vm->map[aim];
}

void		ft_add(t_process **proc)
{
	int		ret;

	ret = (*proc)->registers[(*proc)->fetchqueue[0][1]] +
	(*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = ret;
	(*proc)->carry = (!ret ? 1 : 0);
}

void		ft_sub(t_process **proc)
{
	int		ret;
	
	ret = (*proc)->registers[(*proc)->fetchqueue[0][1]] -
	(*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = ret;
	(*proc)->carry = (!ret ? 1 : 0);
}

void		ft_or(t_process **proc)
{
	if ((*proc)->fetchqueue[0][0] == 1)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] |
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] |
				(*proc)->fetchqueue[1][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] |
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] |
				(*proc)->fetchqueue[1][1];
		}
	}

}

void		ft_and(t_process **proc)
{
	if ((*proc)->fetchqueue[0][0] == 1)
	{
		if ((*proc)->fetchqueue[1][0] == 1)
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] &
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] &
				(*proc)->fetchqueue[1][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] &
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] &
				(*proc)->fetchqueue[1][1];
		}
	}
}
