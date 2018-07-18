/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct3.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:02:59 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 18:08:07 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_lfork(t_process **proc)
{
	int aim;

	aim = (*proc)->registers[0] + (*proc)->fetchqueue[0][1];
	//creer un nouveau process a g_vm->map[aim];
}

void		ft_add(t_process **proc)
{
	(*proc)->registers[(*proc)->fetchqueue[2][1]] =
	(*proc)->registers[(*proc)->fetchqueue[0][1]] +
	(*proc)->registers[(*proc)->fetchqueue[1][1]];
}

void		ft_sub(t_process **proc)
{
	(*proc)->registers[(*proc)->fetchqueue[2][1]] =
	(*proc)->registers[(*proc)->fetchqueue[0][1]] -
	(*proc)->registers[(*proc)->fetchqueue[1][1]];
}

void		ft_or(t_process **proc)
{
	(void)proc;
}

void		ft_and(t_process **proc)
{
	(void)proc;
}
