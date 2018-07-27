/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_free.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:01:00 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 19:35:21 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

static void		free_champs(void)
{
	unsigned int		i;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		ft_strdel(&g_vm->champion[i]->name);
		ft_strdel(&g_vm->champion[i]->comment);
		ft_strdel(&g_vm->champion[i]->filename);
		ft_strdel((char **)&g_vm->champion[i]->instructions);
		if (g_vm->champion[i])
			free(g_vm->champion[i]);
	}
	if (g_vm->champion)
		free(g_vm->champion);
}

int				free_all(void)
{
	unsigned int	i;
	t_process		*proc;
	t_process		*tmp;

	proc = NULL;
	proc = g_vm->list_process;
	i = -1;
	ft_strdel(&g_vm->p_map);
	ft_strdel((char **)&g_vm->map);
	free_champs();
	while (proc)
	{
		free(proc->reg);
		tmp = proc;
		proc = proc->next;
		free(tmp);
	}
	if (g_vm)
		free(g_vm);
	return (0);
}

void			free_process(t_process *list)
{
	free(list->reg);
	free(list);
}
