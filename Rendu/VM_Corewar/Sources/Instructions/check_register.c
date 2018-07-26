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

int				check_registers(t_process *proc)
{
	int		i;
	t_op info;

	i = -1;
	info = get_opcode(proc->op);
	while (++i < info.nparams && i < 3)
		if ((proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] < 1) ||
				(proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] > 16))
			return (0);
	return (1);
}
