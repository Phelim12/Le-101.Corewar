/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   functions_one.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: magaspar <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 15:01:37 by magaspar     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 14:32:54 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int			find_player(t_process **proc)
{
	int player;
	
	while (player < g_vm->nb_players)
	{
		if ((*proc)->registers[1] == g_vm->champion[player]->num)
			return (g_vm->champion[player]->num);
		player++;
	}
	return (-1);
}

void		ft_live(t_process **proc)
{
	int player;

	player = find_player(proc);
	/*if (is_win(proc))
	{
		//check_win before/after cycle ?
	}*/
	//if (is_live(proc))
	//{
		(*proc)->live++;
		g_vm->champion[player]->live += 1;
	//}
}
