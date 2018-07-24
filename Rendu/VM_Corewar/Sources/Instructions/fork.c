/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fork.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:01:23 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 13:41:17 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_fork(int pc)
{
	dprintf(1, "aim = %d\n", pc);
}

void		ft_fork(t_process **proc, t_process **begin)
{
	t_process 		*tmp;
	int				var;
	int				aim;

	var = -1;
	tmp = ft_memalloc(sizeof(t_process));
	aim = ((*proc)->begin + ((*proc)->fetchqueue[0][1] % IDX_MOD) % MEM_SIZE);
	tmp->live = 0;
	tmp->begin = aim;
	tmp->cycle_delay = -1;
	tmp->carry = (*proc)->carry;
	tmp->op = 0;
	tmp->registers = malloc(REG_SIZE * (REG_NUMBER + 1));
	ft_memcpy(tmp->registers, (*proc)->registers, REG_SIZE * REG_NUMBER);
	tmp->registers[0] = aim;
	while (++var < 4)
	{
		tmp->fetchqueue[var][0] = 0;
		tmp->fetchqueue[var][1] = -1;
	}	
	g_vm->nb_proc++;
	tmp->num = g_vm->nb_proc;
	tmp->next = *begin;
	*begin = tmp;
}


/*void	exec_fork()
{
	t_process	**proc;
	t_process	*begin;

	proc = &g_vm->list_process;
	begin = g_vm->list_process;	
	//	print_instruction(*proc);
	while (*proc)
	{
		if (((*proc)->op == 12 || (*proc)->op == 15) &&
				(*proc)->cycle_delay == 0)
		{
			if (g_vm->v)
				print_instruction(*proc);
			if ((*proc)->op == 12)
			{
				ft_printf("CURSOR = %d\n", (*proc)->registers[0]);
				ft_print_nb_proc(begin);
				ft_fork(proc, &begin);
				ft_print_nb_proc(begin);
				ft_printf("AFTER = %d\n", (*proc)->registers[0]);
			}
			else if ((*proc)->op == 15)
				ft_lfork(proc, &begin);
			(*proc)->cycle_delay = -1;
		}
		(*proc) = (*proc)->next;
	}
	g_vm->list_process = begin;
}*/
