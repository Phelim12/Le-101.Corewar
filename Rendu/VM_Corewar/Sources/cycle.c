/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:21:07 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 22:09:17 by dguelpa     ###    #+. /#+    ###.fr     */
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
//			int j = 0;
/*			dprintf(2,"OPCODE = %d | %s | type %d value %d | type %d value %d | type %d value %d\n", (*proc)->op, instruction.name,
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
	int		i;

	i = -1;
	//	if (g_vm->map[cursor] > 0xff || g_vm->map[cursor] < 0x40)
	(*proc)->fetchqueue[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	(*proc)->fetchqueue[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	(*proc)->fetchqueue[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	(*proc)->fetchqueue[3][0] = g_vm->map[cursor]  & 0x3;
//		while (++i < 4)
//			dprintf(2, "type = %d\n", (*proc)->fetchqueue[i][0]);
	if (check_ocp((*proc)->op, cursor))
		(*proc)->op = -1;
//	dprintf(2, "\n<<<<<<<<\nproc op = %d\n", (*proc)->op);
	return (read_params(++cursor, instruction, proc));
}

static void				read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

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
/*
	if (instruction.info_params)
		(*proc)->registers[0] = read_ocp(++cursor, instruction, proc) % MEM_SIZE;
	else
		(*proc)->registers[0] = read_params(++cursor, instruction, proc) % MEM_SIZE;
*/
	//	dprintf(2, "LE VRAI PC EST = %d\n", (*proc)->registers[0]);
}

void	print_instruction(t_process *proc)
{
	char	*s;
	t_op	*tab;
	int		f;
	int		i;

	i = -1;
	f = 0;
	s = NULL;
	tab = get_op_tab();
	// ft_printf("\n%d", g_vm->map[proc->begin] - 1);
	ft_printf("\nP%d |\t%s", abs(proc->num), tab[proc->op - 1].name);
	if (g_vm->v >= 1)
	{
		while (++i < tab[proc->op - 1].nparams)
		{
			if (proc->fetchqueue[i][0] == 1)
				ft_printf((f ? ", r%d" : "\tr%d"), proc->fetchqueue[i][1]);
			else if (proc->fetchqueue[i][0] == 2)
				ft_printf((f ? ", %%%d" : "\t%%%d"), proc->fetchqueue[i][1]);
			else
				ft_printf((f ? ", %d" : "\t%d"), proc->fetchqueue[i][1]);
			f = 1;
		}
	}
	if (g_vm->v >= 2)
		ft_printf((g_vm->v >= 3 ? "\t\tPC -> %d\n" : "\t\tPC -> %d"), proc->begin);
	if (g_vm->v < 3)
		ft_printf("\t\tCycle %d\n", g_vm->cycle + 1);
	else
		ft_printf("\n");
}

void	run(t_process *proc)
{
	//dprintf(2, "PC = %d\n", proc->registers[0]);
	//	print_instruction(proc);
	// ft_printf("OP = %d\n", proc->op);
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

static void	ft_print_nb_proc(t_process *begin)
{
	t_process 	*tmp;
	int 		var;

	var = 0;
	tmp = begin;
	while (tmp)
	{
		var++;
		tmp = tmp->next;
	}
//	dprintf(2, "NB_PROC = %d\n", var);
}

void	exec_live()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
	//	print_instruction(*proc);
	while (*proc)
	{
		if ((*proc)->op == 1 && (*proc)->cycle_delay == 0)
			read_instruction(proc);
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
	while (*proc)
	{
		if ((*proc)->op == 1 && (*proc)->cycle_delay == 0)
		{
			if (g_vm->v)
				print_instruction(*proc);
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
	//	print_instruction(*proc);
	while (*proc)
	{
		if (((*proc)->op == 12 || (*proc)->op == 15)
				&& (*proc)->cycle_delay == 0)
		read_instruction(proc);
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
	while (*proc)
	{
		if (((*proc)->op == 12 || (*proc)->op == 15) &&
				(*proc)->cycle_delay == 0)
		{
			if (g_vm->v)
				print_instruction(*proc);
			if ((*proc)->op == 12)
			{
				// ft_print_nb_proc(begin);
				ft_fork(proc, &begin);
			}
			else if ((*proc)->op == 15)
				ft_lfork(proc, &begin);
			(*proc)->cycle_delay = -1;
		}
		(*proc) = (*proc)->next;
	}
	//(*proc) = g_vm->list_process;
	g_vm->list_process = begin;
}

void	exec_process()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;
/*	while (*proc)
	{
		if ((*proc)->cycle_delay == 0 && (*proc)->op != 1 &&
				(*proc)->op != 12 && (*proc)->op != 15)
		read_instruction(proc);
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;*/
	while (*proc)
	{
//		if ((*proc)->op > 0)
//		{
	//	dprintf(1, "exec_process player %d\n", (*proc)->registers[1]);
//	dprintf(2, "BONJOUR1\n");
			if ((*proc)->cycle_delay == -1)
			{
				if (g_vm->map[(*proc)->registers[0]] > 0 &&
					g_vm->map[(*proc)->registers[0]] < 17)
						read_opcode(proc);
				else
				{
					if ((*proc)->registers[0] == MEM_SIZE - 1)
							(*proc)->registers[0] = -1;
					(*proc)->registers[0] += 1;
				}
			}
			if ((*proc)->cycle_delay == 0 && (*proc)->op != 1 &&
					(*proc)->op != 12 && (*proc)->op != 15)
			{
//				dprintf(2, "WHUT\n");
				read_instruction(proc);
				if ((*proc)->op > 0 && check_registers(*proc))
				{
					if (g_vm->v)
						print_instruction(*proc);
					run(*proc);
					(*proc)->cycle_delay = -1;
				}
				else
				{
	//				dprintf(2, "BONJOUR\n");
					(*proc)->op = -1;
					(*proc)->cycle_delay = -1;
				}
			}
/*			else if ((*proc)->cycle_delay == -1)
			{
				 if (g_vm->map[(*proc)->registers[0]] > 0 &&
					g_vm->map[(*proc)->registers[0]] < 17)
						read_opcode(proc);
				else
				{
					if ((*proc)->registers[0] == MEM_SIZE - 1)
							(*proc)->registers[0] = -1;
					(*proc)->registers[0] += 1;
				}
			}*/
//		}
//		else if (!(*proc)->cycle_delay)
//			(*proc)->cycle_delay = -1;
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
//		dprintf(2, "PC = %d | Player : %d\n", (*proc)->registers[0], (*proc)->registers[1]);
//		dprintf(2, "cycle_delay = %d\n------------------------------------------------\n", (*proc)->cycle_delay);
		if ((*proc)->cycle_delay == -1)
		{
			if (g_vm->map[(*proc)->registers[0]] > 0 &&
					g_vm->map[(*proc)->registers[0]] < 17)
				read_opcode(proc);

/*			else
			{
				if ((*proc)->registers[0] == MEM_SIZE - 1)
					(*proc)->registers[0] = -1;
				(*proc)->registers[0] += 1;
			}*/
			if (g_vm->dump >= 4)
				ft_printf("Player %d => PC %d\n", (*proc)->registers[1], (*proc)->registers[0]);
		}//jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		else if ((*proc)->cycle_delay > 0)
		{
			(*proc)->cycle_delay--;
			if (g_vm->v >= 4)
				ft_printf("Player %d => Instruction %d : %d cycles to wait\n", (*proc)->registers[1], (*proc)->op, (*proc)->cycle_delay);
		}
		*proc = (*proc)->next;
	}
	g_vm->list_process = begin;
	return (0);
}
