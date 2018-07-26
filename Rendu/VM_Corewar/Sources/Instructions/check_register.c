/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_register.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:24:47 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 22:07:50 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

int		check_reg(t_process *proc)
{
	t_op	info;
	int		i;

	i = -1;
	info = get_opcode(proc->op);
	while (++i < info.nparams)
		if ((proc->params[i][0] == REG_CODE) &&
			(proc->params[i][1] < MIN_REG || proc->params[i][1] > MAX_REG))
			return (0);
	return (1);
}
