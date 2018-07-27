/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   run.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 01:11:33 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 01:21:24 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void			read_opcode(t_process **proc)
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

void static		go(t_process **proc, t_process **begin)
{
	read_instruction(proc);
	if (PROC->op > 0 && check_reg(*proc))
	{
		run(proc, begin);
		PROC->cycle_delay = -1;
	}
	else
	{
		PROC->op = -1;
		PROC->cycle_delay = -1;
	}
}

void			lets_process(void)
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
