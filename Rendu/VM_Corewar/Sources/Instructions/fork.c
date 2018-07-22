/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:01:23 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:21:28 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_fork(int pc)
{
	dprintf(1, "aim = %d\n", pc);
}

void		ft_fork(t_process **proc, t_process **begin)
{
	int				aim;
	t_process		*new;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
//	debug_fork(aim);
	new = lstnew_vm((*proc)->registers, REG_SIZE * REG_NUMBER);
	new->registers[0] = aim;
	lstadd_vm(begin, new);
}
