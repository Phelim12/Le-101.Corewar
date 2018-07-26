/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:21:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 02:00:08 by dguelpa     ###    #+. /#+    ###.fr     */
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
	if ((*proc)->op > 0)
	{
		while (((*proc)->fetchqueue[i][0] || (!instruction.info_params && !param))
				&& i < instruction.nparams)
		{
			//	dprintf(2, "WHILE OP %d\n", (*proc)->op);
			if ((*proc)->fetchqueue[i][0] == 1)
				(*proc)->fetchqueue[i][1] = get_reg(cursor++);
			else if ((*proc)->fetchqueue[i][0] == 2 || instruction.opcode == 1)
			{
				(*proc)->fetchqueue[i][1] = get_dir(cursor, instruction);
				cursor += (instruction.size_dir == 1 ? 2 : 4);
			}
			else if ((*proc)->fetchqueue[i][0] == 3 || instruction.opcode == 9 ||
					instruction.opcode == 12 || instruction.opcode == 15)
			{
				(*proc)->fetchqueue[i][1] = (short)get_ind(cursor);
				cursor += 2;
			}
			param++;
			i++;
		}
	}
	else if ((*proc)->op < 0)
	{
		i = -1;
		while (++i < instruction.nparams)
		{
			if ((*proc)->fetchqueue[i][0] == 1)
				cursor++;
			else if ((*proc)->fetchqueue[i][0] == 2)
				cursor += (instruction.size_dir == 1 ? 2 : 4);
			else if ((*proc)->fetchqueue[i][0] == 3)
				cursor += 2;
		}
		if (g_vm->v >= 4)
			ft_printf("\tJUMP Player %d : %d => %d\n", (*proc)->registers[0], (*proc)->begin, cursor);
	}
	//	dprintf(2, "cursor = %d\n", cursor);
/*				int j = 0;
				dprintf(2,"OPCODE = %d | %s | type %d value %d | type %d value %d | type %d value %d\n", (*proc)->op, instruction.name,
						(*proc)->fetchqueue[0][0], (*proc)->fetchqueue[0][1],
						(*proc)->fetchqueue[1][0], (*proc)->fetchqueue[1][1],
						(*proc)->fetchqueue[2][0], (*proc)->fetchqueue[2][1]);*/
	//dprintf(2,"PC = %d\n", (*proc)->registers[0]);
	/*	while (j < 4)
		{
		ft_printf("fetch[%d][0] = %d\n", j, (*proc)->fetchqueue[j][0]);
		ft_printf("fetch[%d][1] = %d\n", j, (*proc)->fetchqueue[j][1]);
		j++;
		}
		*/
	return (((*proc)->op == 9 && (*proc)->carry) ? (*proc)->begin : cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	(*proc)->fetchqueue[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	(*proc)->fetchqueue[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	(*proc)->fetchqueue[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	(*proc)->fetchqueue[3][0] = g_vm->map[cursor]  & 0x3;
/*	int i = -1;
	while (++i < 4)
		dprintf(2, "type = %d\n", (*proc)->fetchqueue[i][0]);*/
	if (check_ocp((*proc)->op, cursor))
		(*proc)->op = -1;
//	dprintf(2, "\n<<<<<<<<\nproc op = %d\n", (*proc)->op);
	return (read_params(++cursor, instruction, proc));
}

static void				read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

//	dprintf(2, "READ_INSTRUCTION : OP = %d\n", (*proc)->op);
	cursor = (*proc)->registers[0];
	instruction = get_opcode((*proc)->op);
	if (instruction.info_params)
		(*proc)->registers[0] = read_ocp(++cursor, instruction, proc) % MEM_SIZE;
	else
		(*proc)->registers[0] = read_params(++cursor, instruction, proc) % MEM_SIZE;
}

static void				read_opcode(t_process **proc)
{
	t_op	instruction;
	int		cursor;
	int		i;

	//	dprintf(2, "READ_OPCODE : %d\n", (*proc)->op);
	//	dprintf(2, "rd_instr\n");
	i = 0;
	while (i < 4)
	{
		(*proc)->fetchqueue[i][0] = 0;
		(*proc)->fetchqueue[i++][1] = -1;
	}
	cursor = (*proc)->registers[0];
	instruction = get_opcode(g_vm->map[cursor]);
	(*proc)->op = g_vm->map[cursor];
	(*proc)->begin = cursor;
	(*proc)->cycle_delay = instruction.cycles - 1;
	//   dprintf(2, "----------------------\n");
	//		dprintf(2, "PC %d | OPCODE = %d\n", (*proc)->registers[0],  g_vm->map[cursor]);
	//		dprintf(2, "instruction = %s\n", instruction.name);
	//		dprintf(1, "info params = %d\n", instruction.info_params);
	//		dprintf(2, "opcode = %d\ninforparams = %d\n", (*proc)->op, instruction.info_params);
	//		dprintf(2, "----------------------\n");
}

void					lets_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while (*proc)
	{
//		dprintf(2, "cycle_delay : %d\n", (*proc)->cycle_delay);
		if ((*proc)->cycle_delay > 0)
			(*proc)->cycle_delay--;
		if ((*proc)->cycle_delay == -1)
		{
			if (g_vm->map[(*proc)->registers[0]] > 0 &&
					g_vm->map[(*proc)->registers[0]] < 17)
				read_opcode(proc);
			else
				(*proc)->registers[0] = ((*proc)->registers[0] + 1) % MEM_SIZE;
		}
		else if ((*proc)->cycle_delay == 0)
		{
			read_instruction(proc);
			if ((*proc)->op > 0 && check_registers(*proc))
			{
				if (g_vm->v)
					print_instruction(*proc);
				run(proc, &begin);
				(*proc)->cycle_delay = -1;
			}
			else
			{
				(*proc)->op = -1;
				(*proc)->cycle_delay = -1;
			}
		}
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
}
