/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_cycle.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 23:44:30 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 23:57:12 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void	run(t_process **proc, t_process **begin)
{
	if (PROC->op == 1)
		ft_live(proc);
	else if (PROC->op == 2)
		ft_ld(proc);
	else if (PROC->op == 3)
		ft_st(proc);
	else if (PROC->op == 4)
		ft_add(proc);
	else if (PROC->op == 5)
		ft_sub(proc);
	else if (PROC->op == 6)
		ft_and(proc);
	else if (PROC->op == 7)
		ft_or(proc);
	else if (PROC->op == 8)
		ft_xor(proc);
	else if (PROC->op == 9)
		ft_zjmp(proc);
	else if (PROC->op == 10)
		ft_ldi(proc);
	else if (PROC->op == 11)
		ft_sti(proc);
	else if (PROC->op == 12)
		ft_fork(proc, begin);
	else if (PROC->op == 13)
		ft_lld(proc);
	else if (PROC->op == 14)
		ft_lldi(proc);
	else if (PROC->op == 15)
		ft_lfork(proc, begin);
	else if (PROC->op == 16)
		ft_aff(proc);
}

void	ft_print_nb_proc(t_process *begin)
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
	ft_printf("\nP%d |\t%s", abs(proc->num), tab[proc->op - 1].name);
	if (g_vm->v >= 1)
	{
		while (++i < tab[proc->op - 1].nparams)
		{
			if (proc->params[i][0] == 1)
				ft_printf((f ? ", r%d" : "\tr%d"), proc->params[i][1]);
			else if (proc->params[i][0] == 2)
				ft_printf((f ? ", %%%d" : "\t%%%d"), proc->params[i][1]);
			else
				ft_printf((f ? ", %d" : "\t%d"), proc->params[i][1]);
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
