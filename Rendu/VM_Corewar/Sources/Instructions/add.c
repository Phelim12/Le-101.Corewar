/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:08:51 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:20:53 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_add(t_process **proc)
{
	PROC->reg[PROC->params[2][1]] = (PROC->reg[PROC->params[0][1]] +
		PROC->reg[PROC->params[1][1]]);
	PROC->carry = (!PROC->reg[PROC->params[2][1]] ? 1 : 0);
}
