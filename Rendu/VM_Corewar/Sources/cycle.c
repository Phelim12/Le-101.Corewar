/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 14:41:47 by jjanin-r    ###    #+. /#+    ###.fr     */
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
	ft_printf("OPCODE = %d | %s | type %d value %d | type %d value %d | type %d value %d\n", (*proc)->op, instruction.name,
			(*proc)->fetchqueue[0][0], (*proc)->fetchqueue[0][1],
			(*proc)->fetchqueue[1][0], (*proc)->fetchqueue[1][1],
			(*proc)->fetchqueue[2][0], (*proc)->fetchqueue[2][1],
			(*proc)->fetchqueue[3][0], (*proc)->fetchqueue[3][1]);
	ft_printf("PC = %d\n", (*proc)->registers[0]);
/*	while (j < 4)
	{
		ft_printf("fetch[%d][0] = %d\n", j, (*proc)->fetchqueue[j][0]);
		ft_printf("fetch[%d][1] = %d\n", j, (*proc)->fetchqueue[j][1]);
		j++;
	}
*/	return (cursor);
}

static int			read_ocp(int cursor, t_op instruction, t_process **proc)
{

	(*proc)->fetchqueue[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	(*proc)->fetchqueue[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	(*proc)->fetchqueue[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	(*proc)->fetchqueue[3][0] = g_vm->map[cursor] & 0x3;
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
	(*proc)->cycle_delay = instruction.cycles;
	(*proc)->op = g_vm->map[cursor];
	(*proc)->begin = cursor;
//	dprintf(1, "PC = %d | Player : %d\n", (*proc)->registers[0], (*proc)->registers[1]);
//	ft_printf("OPCODE = %d\n", g_vm->map[cursor]);
//	ft_printf("instruction = %s\n", instruction.name);
//	dprintf(1, "info params = %d\n", instruction.info_params);
	if (instruction.info_params)
		(*proc)->registers[0] = read_ocp(++cursor, instruction, proc) % MEM_SIZE;
	else
		(*proc)->registers[0] = read_params(++cursor, instruction, proc) % MEM_SIZE;
}

void	run(t_process *proc)
{
	if (proc->op == 2)
		ft_ld(&proc);
	if (proc->op == 3)
		ft_st(&proc);
	if (proc->op == 4)
		ft_add(&proc);
	if (proc->op == 5)
		ft_sub(&proc);
	if (proc->op == 6)
		ft_and(&proc);
	if (proc->op == 7)
		ft_or(&proc);
	if (proc->op == 8)
		ft_xor(&proc);
	if (proc->op == 9)
		ft_zjmp(&proc);
	if (proc->op == 10)
		ft_ldi(&proc);
	if (proc->op == 11)
		ft_sti(&proc);
	if (proc->op == 13)
		ft_lld(&proc);
	if (proc->op == 14)
		ft_lldi(&proc);
	if (proc->op == 16)
		ft_aff(&proc);
}

void	exec_live()
{
	t_process *proc;

	proc = g_vm->list_process;
	while (proc)
	{
		if (proc->op == 1)
			ft_live(&proc);
		proc = proc->next;
	}
}

void	exec_fork()
{
	t_process *proc;

	proc = g_vm->list_process;
	while (proc)
	{
		if (proc->op == 12)
			ft_fork(&proc);
		if (proc->op == 15)
			ft_lfork(&proc);
		proc = proc->next;
	}
}

void	exec_process()
{
	t_process *proc;

	proc = g_vm->list_process;
	while (proc)
	{
		dprintf(1, "exec_process player %d\n", proc->registers[1]);
		if (check_registers(proc))
			run(proc);
		proc = proc->next;
	}
}

int		cycle_process()
{
	t_process	*proc;

	proc = g_vm->list_process;
	while (proc)
	{
		if (proc->cycle_delay == -1)
		{
			read_instruction(&proc); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		}
		else if (proc->cycle_delay > 0)
			proc->cycle_delay--;
		proc = proc->next;
	}
	return (0);
}

/*
void			*exec_process()
{

}
*/
