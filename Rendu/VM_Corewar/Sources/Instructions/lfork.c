/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lfork.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:54:13 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:21:45 by jjanin-r    ###    #+. /#+    ###.fr     */
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
	int				aim;
	t_process		*new;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
//	debug_lfork(aim);
	new = lstnew_vm((*proc)->registers, REG_SIZE * REG_NUMBER);
	new->registers[0] = aim;
	lstadd_vm(begin, new);
}
