/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lfork.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:54:13 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 14:11:15 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_lfork(t_process **proc, t_process **begin)
{
	t_process		*new;
	int				aim;

	new = lstnew_vm(PROC->reg, REG_SIZE * REG_NUMBER + 4);
	aim = (PROC->begin + (PROC->params[0][1])) % MEM_SIZE;
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
