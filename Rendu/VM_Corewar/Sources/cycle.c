/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:21:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 02:32:19 by jjanin-r    ###    #+. /#+    ###.fr     */
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
			PROC->params[i][1] = get_reg(cursor++);
			cursor %= MEM_SIZE;
		}
		else if (PROC->params[i][0] == 2 || instruction.opcode == 1)
		{
			PROC->params[i][1] = get_dir(cursor, instruction);
			cursor += (instruction.size_dir == 1 ? 2 : 4);
			cursor %= MEM_SIZE;
		}
		else if (PROC->params[i][0] == 3 || instruction.opcode == 9 ||
				instruction.opcode == 12 || instruction.opcode == 15)
		{
			PROC->params[i][1] = (short)get_ind(cursor);
			cursor = (2 + cursor) % MEM_SIZE;
		}
	}
	return (cursor);
}

static int		jump(int cursor, t_op instruction, t_process **proc)
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

static int		read_params(int cursor, t_op instruction, t_process **proc)
{
	if (PROC->op > 0)
		cursor = valid_ocp(cursor, instruction, proc);
	else if (PROC->op < 0)
		cursor = jump(cursor, instruction, proc);
	if (PROC->op == 9 && PROC->carry)
		return (PROC->begin);
	return (cursor);
}

static int		read_ocp(int cursor, t_op instruction, t_process **proc)
{
	PROC->params[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	PROC->params[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	PROC->params[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	PROC->params[3][0] = g_vm->map[cursor] & 0x3;
	if (check_ocp(PROC->op, cursor))
		PROC->op = -1;
	return (read_params(++cursor % MEM_SIZE, instruction, proc));
}

void			read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

	cursor = PROC->reg[0];
	instruction = get_opcode(PROC->op);
	if (instruction.info_params)
		PROC->reg[0] = read_ocp(++cursor % MEM_SIZE, instruction, proc) %
			MEM_SIZE;
	else
		PROC->reg[0] = read_params(++cursor % MEM_SIZE, instruction, proc) %
			MEM_SIZE;
}