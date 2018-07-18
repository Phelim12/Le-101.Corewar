/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct4.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:06:55 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 18:50:17 by jjanin-r    ###    #+. /#+    ###.fr     */
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
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->registers[(*proc)->fetchqueue[0][1]] ^
				(*proc)->fetchqueue[1][1];
		}
	}
	else
	{
		if ((*proc)->fetchqueue[1][0] == 1)
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] ^
				(*proc)->registers[(*proc)->fetchqueue[1][1]];
		}
		else
		{
			(*proc)->registers[(*proc)->fetchqueue[2][1]] =
				(*proc)->fetchqueue[0][1] ^
				(*proc)->fetchqueue[1][1];
		}
	}
}
