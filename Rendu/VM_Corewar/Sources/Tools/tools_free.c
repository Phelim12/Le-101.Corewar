/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:01:00 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 16:03:30 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

int		free_all(void)
{
	unsigned int i;

	i = 0;
	while (i < g_vm->nb_players)
		free(g_vm->champion[i++]);
	free(g_vm->champion);
	ft_strdel(&g_vm->p_map);
	ft_strdel((char **)&g_vm->map);
	free(g_vm);
	return (0);
}

void	free_process(t_process *list)
{
	free(list->reg);
	free(list);
}
