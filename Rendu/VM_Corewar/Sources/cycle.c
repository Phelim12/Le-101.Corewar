/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:21:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:21:31 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int			read_params(int cursor, t_op instruction, t_process **proc)
{
	int i;
	int param;

	param = 0;
	i = 0;
	//		dprintf(2, "cursor in rd_params = %d\n", cursor);
	if (PROC->op > 0)
	{
		while ((PROC->params[i][0] || (!instruction.info_params && !param))
				&& i < instruction.nparams)
		{
			//	dprintf(2, "WHILE OP %d\n", PROC->op);
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
				cursor += 2;
				cursor %= MEM_SIZE;
			}
			param++;
			i++;
		}
	}
	else if (PROC->op < 0)
	{
		i = -1;
		while (++i < instruction.nparams)
		{
			if (PROC->params[i][0] == 1)
			{
				cursor++;
				cursor %= MEM_SIZE;
			}
			else if (PROC->params[i][0] == 2)
			{
				cursor += (instruction.size_dir == 1 ? 2 : 4);
				cursor %= MEM_SIZE;
			}
			else if (PROC->params[i][0] == 3)
			{
				cursor += 2;
				cursor %= MEM_SIZE;
			}
		}
		if (g_vm->v >= 4)
			ft_printf("\tJUMP Player %d : %d => %d\n", PROC->reg[0], PROC->begin, cursor);
	}
	//	dprintf(2, "cursor = %d\n", cursor);
/*				int j = 0;
				dprintf(2,"OPCODE = %d | %s | type %d value %d | type %d value %d | type %d value %d\n", PROC->op, instruction.name,
						PROC->params[0][0], PROC->params[0][1],
						PROC->params[1][0], PROC->params[1][1],
						PROC->params[2][0], PROC->params[2][1]);*/
	//dprintf(2,"PC = %d\n", PROC->reg[0]);
	/*	while (j < 4)
		{
		ft_printf("fetch[%d][0] = %d\n", j, PROC->params[j][0]);
		ft_printf("fetch[%d][1] = %d\n", j, PROC->params[j][1]);
		j++;
		}
		*/
	return ((PROC->op == 9 && PROC->carry) ? PROC->begin : cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	PROC->params[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	PROC->params[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	PROC->params[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	PROC->params[3][0] = g_vm->map[cursor]  & 0x3;
/*	int i = -1;
	while (++i < 4)
		dprintf(2, "type = %d\n", PROC->params[i][0]);*/
	if (check_ocp(PROC->op, cursor))
		PROC->op = -1;
//	dprintf(2, "\n<<<<<<<<\nproc op = %d | num : %d\n", PROC->op, PROC->num);
	return (read_params(++cursor % MEM_SIZE, instruction, proc));
}

static void				read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

//	dprintf(2, "READ_INSTRUCTION : OP = %d\n", PROC->op);
	cursor = PROC->reg[0];
	instruction = get_opcode(PROC->op);
	if (instruction.info_params)
		PROC->reg[0] = read_ocp(++cursor % MEM_SIZE, instruction, proc) % MEM_SIZE;
	else
		PROC->reg[0] = read_params(++cursor % MEM_SIZE, instruction, proc) % MEM_SIZE;
}

static void				read_opcode(t_process **proc)
{
	t_op	instruction;
	int		cursor;
	int		i;

//		dprintf(2, "READ_OPCODE : %d\n", PROC->op);
	//	dprintf(2, "rd_instr\n");
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
	//   dprintf(2, "----------------------\n");
	//		dprintf(2, "PC %d | OPCODE = %d\n", PROC->reg[0],  g_vm->map[cursor]);
	//		dprintf(2, "instruction = %s\n", instruction.name);
	//		dprintf(1, "info params = %d\n", instruction.info_params);
	//		dprintf(2, "opcode = %d\ninforparams = %d\n", PROC->op, instruction.info_params);
	//		dprintf(2, "----------------------\n");
}

void					lets_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while PROC
	{
//		dprintf(2, "PC %d |Num_proc : %d\n", PROC->reg[0], PROC->num);
//		dprintf(2, "cycle_delay : %d\n", PROC->cycle_delay);
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
		{
			read_instruction(proc);
			if (PROC->op > 0 && check_reg(*proc))
			{
				if (g_vm->v)
					print_instruction(*proc);
				run(proc, &begin);
				PROC->cycle_delay = -1;
			}
			else
			{
				PROC->op = -1;
				PROC->cycle_delay = -1;
			}
		}
		PROC = PROC->next;
	}
	g_vm->list_process = begin;
}
