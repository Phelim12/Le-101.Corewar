/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:25:00 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:22:02 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_live(t_process **proc, int player, int debug)
{
	int		j;

	j = -1;
	if (debug == 1)
		dprintf(1, "RUN LIVE Player %d\n", (*proc)->registers[1]);
	else if (debug == 2)
		ft_printf("Current proc lives = %d\n", (*proc)->live);
	else if (debug == 3)
		ft_printf("Current proc lives = %d\n", (*proc)->live);
	else if (debug == 4)
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
				player, g_vm->champion[player]->name);
	else if (debug == 5)
	{
		while (++j < 2)
			ft_printf("Player %d has %d lives\n", j, g_vm->champion[j]->live);
	}
}

void		ft_live(t_process **proc)
{
	int				player;
	unsigned int	i;

	i = 0;
	player = 0;
//	debug_live(proc, player, 1);
	while (i < g_vm->nb_players)
	{
		if (g_vm->champion[i]->num == (*proc)->fetchqueue[0][1])
		{
			player = g_vm->champion[i]->num;
			break ;
		}
		i++;
	}
//	debug_live(proc, player, 2);
	(*proc)->live++;
//	debug_live(proc, player, 3);
	if (i < g_vm->nb_players)
	{
		g_vm->champion[i]->live++;
		g_vm->last_live = player;
//		debug_live(proc, player, 4);
	}
//	debug_live(proc, player, 5);
}
