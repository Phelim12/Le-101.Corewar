/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rabbit_run.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 14:46:51 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 06:40:13 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int		check_players_process(void)
{
	int				nb;
	t_process		*proc;

	proc = g_vm->list_process;
	nb = 0;
	while (proc)
	{
		nb += 1;
		proc = proc->next;
	}
	return (nb);
}

static int		check_destruction_process(int cycles_passed)
{
	if (cycles_passed + 1 == g_vm->cycle_to_die)
	{
		g_vm->checks++;
		process_remove_if_live(&g_vm->list_process);
		if (g_vm->checks >= MAX_CHECKS)
		{
			g_vm->cycle_to_die -= CYCLE_DELTA;
			g_vm->checks = 0;
		}
		if (g_vm->nb_live >= NBR_LIVE)
		{
			g_vm->cycle_to_die -= CYCLE_DELTA;
			g_vm->checks = 0;
		}
		g_vm->nb_live = 0;
		cycles_passed = -1;
	}
	return (cycles_passed);
}

int				cycling(void)
{
	unsigned int	cycles_passed;
	int				win;

	win = 0;
	cycles_passed = 0;
	while (g_vm->cycle_to_die > 0 && check_players_process() > 0 &&
			(g_vm->dump == 0 || g_vm->cycle <= g_vm->d_cycles))
	{
		process();
		cycles_passed = check_destruction_process(cycles_passed);
		if (!check_players_process())
			break ;
		g_vm->cycle++;
		cycles_passed++;
	}
	if (g_vm->dump == 1 && g_vm->cycle > g_vm->d_cycles)
		ft_dump();
	else
	{
		if (g_vm->last_live != -1)
			win = g_vm->last_live;
		ft_printf("Contestant %d, \"%s\", has won !\n",
				g_vm->champion[win]->num, g_vm->champion[win]->name);
	}
	return (0);
}
