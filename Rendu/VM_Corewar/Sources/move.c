/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 03:56:38 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 04:05:04 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int		valid_ocp(int cursor, t_op instruction, t_process **proc)
{
	int		i;

	i = -1;
	while (++i < instruction.nparams && (PROC->params[i][0] ||
				(!instruction.info_params && !i)))
	{
		if (PROC->params[i][0] == 1)
		{
			PROC->params[i][1] = read_reg(cursor++);
			cursor %= MEM_SIZE;
		}
		else if (PROC->params[i][0] == 2 || instruction.opcode == 1)
		{
			PROC->params[i][1] = read_dir(cursor, instruction);
			cursor += (instruction.size_dir == 1 ? 2 : 4);
			cursor %= MEM_SIZE;
		}
		else if (PROC->params[i][0] == 3 || instruction.opcode == 9 ||
				instruction.opcode == 12 || instruction.opcode == 15)
		{
			PROC->params[i][1] = (short)read_ind(cursor);
			cursor = (2 + cursor) % MEM_SIZE;
		}
	}
	return (cursor);
}

static int		pass_params(int cursor, t_op instruction, t_process **proc)
{
	int		i;

	i = -1;
	while (++i < instruction.nparams)
	{
		if (PROC->params[i][0] == 1)
			cursor = (cursor + 1) % MEM_SIZE;
		else if (PROC->params[i][0] == 2)
		{
			cursor += (instruction.size_dir == 1 ? 2 : 4);
			cursor %= MEM_SIZE;
		}
		else if (PROC->params[i][0] == 3)
			cursor = (cursor + 2) % MEM_SIZE;
	}
	return (cursor);
}

int				read_params(int cursor, t_op instruction, t_process **proc)
{
	if (PROC->op > 0)
		cursor = valid_ocp(cursor, instruction, proc);
	else if (PROC->op < 0)
		cursor = pass_params(cursor, instruction, proc);
	if (PROC->op == 9 && PROC->carry)
		return (PROC->begin);
	return (cursor);
}
