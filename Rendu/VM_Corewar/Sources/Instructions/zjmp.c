/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zjmp.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:02:02 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 02:00:38 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_zjmp(t_process **proc)
{
	if (PROC->carry == 1)
		PROC->reg[0] = (PROC->begin + PROC->params[0][1] % IDX_MOD) % MEM_SIZE;
	if (PROC->reg[0] < 0)
		PROC->reg[0] += MEM_SIZE;
}

