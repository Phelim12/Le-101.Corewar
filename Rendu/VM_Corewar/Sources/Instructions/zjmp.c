/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zjmp.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:02:02 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 14:22:01 by nbettach    ###    #+. /#+    ###.fr     */
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
	if ((*proc)->carry == 1)
		(*proc)->registers[0] =
			((*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD) % MEM_SIZE;
	if ((*proc)->registers[0] < 0)
		(*proc)->registers[0] += MEM_SIZE;
	debug_zjmp(proc);
}
