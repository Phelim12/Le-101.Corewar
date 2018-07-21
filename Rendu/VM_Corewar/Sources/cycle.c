/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/21 13:25:21 by jjanin-r    ###    #+. /#+    ###.fr     */
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
	if ((*proc)->op == -1)
	{
		while (g_vm->map[cursor] < 1 || g_vm->map[cursor] > 16)
			cursor++;
		return (cursor);
	}
	while (((*proc)->fetchqueue[i][0] || (!instruction.info_params && !param))
			&& i < 4)
	{
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
//	int j = 0;
//	ft_printf("OPCODE = %d | %s | type %d value %d | type %d value %d | type %d value %d\n", (*proc)->op, instruction.name,
//			(*proc)->fetchqueue[0][0], (*proc)->fetchqueue[0][1],
//			(*proc)->fetchqueue[1][0], (*proc)->fetchqueue[1][1],
//			(*proc)->fetchqueue[2][0], (*proc)->fetchqueue[2][1],
//			(*proc)->fetchqueue[3][0], (*proc)->fetchqueue[3][1]);
//	ft_printf("PC = %d\n", (*proc)->registers[0]);
/*	while (j < 4)
	{
		ft_printf("fetch[%d][0] = %d\n", j, (*proc)->fetchqueue[j][0]);
		ft_printf("fetch[%d][1] = %d\n", j, (*proc)->fetchqueue[j][1]);
		j++;
	}
*/	return (cursor);
}
/*
typedef struct		s_op
{
	char			*name;
	char			nparams;
	char			params[4];
	char			opcode;
	int				cycles;
	char			*desc;
	char			info_params;
	char			size_dir;
}					t_op;*/


int		size_params(int type)
{
	if (type == 1)
		return (1);
	if (type == 2)
		return (2);
	if (type == 3)
		return (4);
	return (0);
}


static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{
	if (!g_vm->map[cursor])
		(*proc)->op = -1;
	if (((*proc)->fetchqueue[3][0] = g_vm->map[cursor] & 0x3))
		(*proc)->op = -1;
	(*proc)->fetchqueue[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	(*proc)->fetchqueue[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	(*proc)->fetchqueue[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	if (instruction.nparams >= 1 && !(size_params((*proc)->fetchqueue[0][0]) & instruction.params[0]))
		(*proc)->op = -1;
	if (instruction.nparams >= 2 && !(size_params((*proc)->fetchqueue[1][0]) & instruction.params[1]))
		(*proc)->op = -1;
	if (instruction.nparams == 3 && !(size_params((*proc)->fetchqueue[2][0]) & instruction.params[2]))
		(*proc)->op = -1;
//	dprintf(2, "rd_ocp : op = %d\n", (*proc)->op);
	return (read_params(++cursor, instruction, proc));
}

static void				read_instruction(t_process **proc)
{
	t_op				instruction;
	int					cursor;
	int				i;

	i = 0;
	while (i < 4)
	{
		(*proc)->fetchqueue[i][0] = 0;
		(*proc)->fetchqueue[i++][1] = -1;
	}
	cursor = (*proc)->registers[0];
	instruction = get_opcode(g_vm->map[cursor]);
	(*proc)->cycle_delay = instruction.cycles - 1;
	(*proc)->op = g_vm->map[cursor];
	(*proc)->begin = cursor;
//	dprintf(1, "PC = %d | Player : %d\n", (*proc)->registers[0], (*proc)->registers[1]);
//	ft_printf("OPCODE = %d\n", g_vm->map[cursor]);
//	ft_printf("instruction = %s\n", instruction.name);
//	dprintf(1, "info params = %d\n", instruction.info_params);
//	dprintf(2, "opcode = %d\ninforparams = %d\n", (*proc)->op, instruction.info_params);
	if (instruction.info_params)
		(*proc)->registers[0] = read_ocp(++cursor, instruction, proc) % MEM_SIZE;
	else
		(*proc)->registers[0] = read_params(++cursor, instruction, proc) % MEM_SIZE;
}

void	run(t_process *proc)
{
	dprintf(2, "op = %d\n PC = %d\n", (*proc).op, proc->registers[0]);
	if (proc->op == 2)
		ft_ld(&proc);
	else if (proc->op == 3)
		ft_st(&proc);
	else if (proc->op == 4)
		ft_add(&proc);
	else if (proc->op == 5)
		ft_sub(&proc);
	else if (proc->op == 6)
		ft_and(&proc);
	else if (proc->op == 7)
		ft_or(&proc);
	else if (proc->op == 8)
		ft_xor(&proc);
	else if (proc->op == 9)
		ft_zjmp(&proc);
	else if (proc->op == 10)
		ft_ldi(&proc);
	else if (proc->op == 11)
		ft_sti(&proc);
	else if (proc->op == 13)
		ft_lld(&proc);
	else if (proc->op == 14)
		ft_lldi(&proc);
	else if (proc->op == 16)
		ft_aff(&proc);
}

void	exec_live()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while (*proc)
	{
		if ((*proc)->op == 1 && (*proc)->cycle_delay == 0)
		{
//			dprintf(1, "exec_process_live player %d\n", (*proc)->registers[1]);
			ft_live(proc);
			(*proc)->cycle_delay = -1;
		}
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
}

void	exec_fork()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while (*proc)
	{
		if (((*proc)->op == 12 || (*proc)->op == 15) &&
			(*proc)->cycle_delay == 0)
		{
			if ((*proc)->op == 12)
				ft_fork(proc, &begin);
			else if ((*proc)->op == 15)
				ft_lfork(proc, &begin);
			(*proc)->cycle_delay = -1;
		}
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
}

void	exec_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while (*proc)
	{
		if ((*proc)->op != -1)
		{
//			dprintf(1, "exec_process player %d\n", (*proc)->registers[1]);
			if (check_registers(*proc) && (*proc)->cycle_delay == 0 &&
				(*proc)->op != 1 && (*proc)->op != 12 && (*proc)->op != 15)
			{
				run(*proc);
				(*proc)->cycle_delay = -1;
			}
		}
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
}

int		cycle_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	while (*proc)
	{
		if ((*proc)->cycle_delay == -1)
			read_instruction(proc); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		else if ((*proc)->cycle_delay > 0)
			(*proc)->cycle_delay--;
		*proc = (*proc)->next;
	}
	g_vm->list_process = begin;
	return (0);
}








