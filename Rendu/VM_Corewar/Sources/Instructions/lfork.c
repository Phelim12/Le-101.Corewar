/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lfork.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:54:13 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 17:01:04 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_lfork(int aim)
{
	dprintf(1, "aim = %d\n", aim);
}

void		ft_lfork(t_process **proc, t_process **begin)
{
	t_process		*new;
	int				aim;

	new = lstnew_vm((*proc)->registers, REG_SIZE * (REG_NUMBER + 1));
	aim = ((*proc)->begin + ((*proc)->fetchqueue[0][1])) % MEM_SIZE;
	aim += (aim < 0 ? MEM_SIZE : 0);
	new->begin = aim;
	new->cycle_delay = -1;
	new->carry = (*proc)->carry;
	new->registers[0] = aim;
	g_vm->nb_proc++;
	new->num = g_vm->nb_proc;
	new->next = *begin;
//	debug_lfork(aim);
	*begin = new;
}
