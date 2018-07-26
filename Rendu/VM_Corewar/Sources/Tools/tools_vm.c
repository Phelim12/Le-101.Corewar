/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 16:46:57 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 15:33:36 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		norme_remove(t_process **list)
{
//	dprintf(2, "it's ok num : %d and lives : %d\n", (*list)->num, (*list)->live);
	(*list)->live = 0;
	(*list) = (*list)->next;
}

void		process_remove_if_live(t_process **begin_list)
{
	t_process	*list;
	t_process	*tmp;

	list = *begin_list;
	while (list)
	{
		if (list == *begin_list && list->live == 0)
		{
//			dprintf(2, "remove first num : %d\n", list->num);
			*begin_list = (*begin_list)->next;
			free_process(list);
			list = *begin_list;
		}
		else if (list->next && list->next->live == 0)
		{
//			dprintf(2, "remove else num : %d\n", list->num);
			tmp = list->next->next;
			free_process(list->next);
			list->next = tmp;
		}
		else
			norme_remove(&list);
	}
}

void	introduction(void)
{
	int i;

	i = g_vm->nb_players - 1;
	ft_printf("Introducing contestants...\n");
	while (i >= 0)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				(g_vm->champion[i]->num >= 0 ? g_vm->champion[i]->num :
				g_vm->champion[i]->num * -1),
				g_vm->champion[i]->prog_size,
				g_vm->champion[i]->name,
				g_vm->champion[i]->comment);
		i--;
	}
}

int		check_data(void)
{
	unsigned int i;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		if (g_vm->champion[i]->prog_size > MEM_SIZE / 6)
			return (error_vm("size", i));
	}
	return (0);
}
