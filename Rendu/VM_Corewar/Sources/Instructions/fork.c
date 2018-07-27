/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:22:09 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 17:19:33 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_fork(t_process **proc, t_process **begin)
{
	t_process		*new;
	int				aim;

	new = lstnew_vm(PROC->reg, REG_SIZE * REG_NUMBER + 10);
	aim = (PROC->begin + PROC->params[0][1] % IDX_MOD) % MEM_SIZE;
	aim += (aim < 0 ? MEM_SIZE : 0);
	new->carry = PROC->carry;
	new->live = PROC->live;
	new->cycle_delay = -1;
	new->reg[0] = aim;
	new->begin = aim;
	g_vm->nb_proc++;
	new->num = g_vm->nb_proc;
	new->next = *begin;
	*begin = new;
}
