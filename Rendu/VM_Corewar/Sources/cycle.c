/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:21:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 00:54:51 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int static			valid_ocp(int cursor, t_op instruction, t_process **proc)
{
	int		i;

	i = 0;
	while ((PROC->params[i][0] || (!instruction.info_params && !i))
			&& i < instruction.nparams)
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
		i++;
	}
	return (cursor);
}

int static			jump(int cursor, t_op instruction, t_process **proc)
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

static int			read_params(int cursor, t_op instruction, t_process **proc)
{
	if (PROC->op > 0)
		cursor = valid_ocp(cursor, instruction, proc);
	else if (PROC->op < 0)
		cursor = jump(cursor, instruction, proc);
	if (PROC->op == 9 && PROC->carry)
		return (PROC->begin);
	return (cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	PROC->params[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	PROC->params[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	PROC->params[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	PROC->params[3][0] = g_vm->map[cursor]  & 0x3;
	if (check_ocp(PROC->op, cursor))
		PROC->op = -1;
	return (read_params(++cursor % MEM_SIZE, instruction, proc));
}

static void			read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

	cursor = PROC->reg[0];
	instruction = get_opcode(PROC->op);
	if (instruction.info_params)
		PROC->reg[0] = read_ocp(++cursor % MEM_SIZE, instruction, proc) % MEM_SIZE;
	else
		PROC->reg[0] = read_params(++cursor % MEM_SIZE, instruction, proc) % MEM_SIZE;
}

static void			read_opcode(t_process **proc)
{
	t_op	instruction;
	int		cursor;
	int		i;

	i = 0;
	while (i < 4)
	{
		PROC->params[i][0] = 0;
		PROC->params[i++][1] = -1;
	}
	cursor = PROC->reg[0];
	instruction = get_opcode(g_vm->map[cursor]);
	PROC->op = g_vm->map[cursor];
	PROC->begin = cursor;
	PROC->cycle_delay = instruction.cycles - 1;
}

void static			go(t_process **proc, t_process **begin)
{
	read_instruction(proc);
	if (PROC->op > 0 && check_reg(*proc))
	{
		if (g_vm->v)
			print_instruction(*proc);
		run(proc, begin);
		PROC->cycle_delay = -1;
	}
	else
	{
		PROC->op = -1;
		PROC->cycle_delay = -1;
	}
}

void				lets_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while PROC
	{
		if (PROC->cycle_delay > 0)
			PROC->cycle_delay--;
		if (PROC->cycle_delay == -1)
		{
			if (g_vm->map[PROC->reg[0]] > 0 &&
					g_vm->map[PROC->reg[0]] < 17)
				read_opcode(proc);
			else
				PROC->reg[0] = (PROC->reg[0] + 1) % MEM_SIZE;
		}
		else if (PROC->cycle_delay == 0)
			go(proc, &begin);
		PROC = PROC->next;
	}
	g_vm->list_process = begin;
}
