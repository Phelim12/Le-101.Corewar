/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_register.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:24:47 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:49:07 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"



int				check_registers_write(t_process *proc)
{
	int		i;

	i = -1;
	while (++i < 3)
		if ((proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] < 1) ||
				(proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] > 16))
			return (0);
	return (1);
}

int				check_registers_read(t_process *proc)
{
	int		i;

	i = -1;
	while (++i < 3)
		if ((proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] < 0) ||
				(proc->fetchqueue[i][0] == 1 && proc->fetchqueue[i][1] > 16))
			return (0);
	return (1);
}

int				check_registers_both(t_process *proc)
{
	int		i;

	i = -1;
	if (proc->op == 3)
	{
		if ((proc->fetchqueue[0][0] == 1 &&
			(proc->fetchqueue[0][1] < 0 || proc->fetchqueue[0][1] > 16)) ||
			(proc->fetchqueue[1][0] == 1 &&
			(proc->fetchqueue[1][1] < 1 || proc->fetchqueue[1][1] > 16)))
			return (0);
	}
	else if (proc->op >= 4 && proc->op <= 8)
	{
		while (++i < 3)
			if (((proc->fetchqueue[i][0] == 1) &&
				(proc->fetchqueue[i][1] < 0 || proc->fetchqueue[i][1] > 16)) ||
				(proc->fetchqueue[2][0] == 1 &&
				(proc->fetchqueue[2][1] < 1 || proc->fetchqueue[i][1] > 16)))
				return (0);
	}
	return (1);
}

int				check_registers_both_next(t_process *proc)
{
	int		i;

	i = -1;
	if (proc->op == 3)
	{
		if ((proc->fetchqueue[0][0] == 1 &&
			(proc->fetchqueue[0][1] < 0 || proc->fetchqueue[0][1] > 16)) ||
			(proc->fetchqueue[1][0] == 1 &&
			(proc->fetchqueue[1][1] < 1 || proc->fetchqueue[1][1] > 16)))
			return (0);
	}
	else if ((proc->op >= 4 && proc->op <= 8) || proc->op == 10 ||
			proc->op == 14)
	{
		while (++i < 3)
			if (((proc->fetchqueue[i][0] == 1) &&
				(proc->fetchqueue[i][1] < 0 || proc->fetchqueue[i][1] > 16)) ||
				(proc->fetchqueue[2][0] == 1 &&
				(proc->fetchqueue[2][1] < 1 || proc->fetchqueue[i][1] > 16)))
				return (0);
	}

	return (1);
}


int				check_registers(t_process *proc)
{
	int		ret;

	ret = 0;
	if (proc->op == 2 || proc->op == 13)
		ret = check_registers_write(proc);
	else if (proc->op == 1 || proc->op == 9 || proc->op == 11 || proc->op == 12 
			|| proc->op == 15 || proc->op == 16)
		ret = check_registers_read(proc);
	else if (proc->op >= 3 && proc->op <= 8)
		ret = check_registers_both(proc);
	else if (proc->op == 10 || proc->op == 14)
		ret = check_registers_both_next(proc);
	return (ret);
}
