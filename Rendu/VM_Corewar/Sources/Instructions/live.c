/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   live.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:25:00 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 01:46:15 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void	ft_live(t_process **proc)
{
	unsigned int	i;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		if (-g_vm->champion[i]->num == PROC->params[0][1])
		{
			g_vm->champion[i]->live++;
			g_vm->last_live = i;
			break ;
		}
	}
	g_vm->nb_live += 1;
	PROC->live++;
}
