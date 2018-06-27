/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:43:36 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 13:16:26 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

/*
**fonction de liste a tester
*/

void	free_process(t_process *list)
{
	free(list->registers);
	free(list->fetchqueue);
	free(list);
}

int		process_remove_if_live(t_process **begin_list, int lives)
{
	t_process	*list;
	t_process	*tmp;

	list = *begin_list;
	while (list && list->next)
		if (list == *begin_list && list->live == 0)
		{
			*begin_list = (*begin_list)->next;
			free_process(list);
			list = *begin_list;
		}
		else if (list->next->live == 0)
		{
			tmp = list->next->next;
			free(list->next);
			list->next = tmp;
		}
		else
		{
			lives += list->live;
			list->live = 0;
			list = list->next;
		}
	return (lives);
}

/*
** ------------------
*/

void	print_usage(void)
{
	ft_printf(USE1);
	ft_printf(USE2);
	ft_printf(USE3);
}

void	check_data(void)
{
	int i;
	char *error;

	error = NULL;
	i = -1;
	while (++i < g_vm->nb_players)
	{
		if (g_vm->champion[i]->prog_size > MEM_SIZE / 6)
			return (ft_error("size", i));
	}
}

void	ft_error(char *s, int c)
{
	unsigned int i;

	i = 0;
	if (!ft_strcmp("size", s))
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n", g_vm->champion[c]->filename, g_vm->champion[c]->prog_size, MEM_SIZE / 6);
	else
		ft_printf(s);
	while (i < g_vm->nb_players)
		free(g_vm->champion[i++]);
	free(g_vm->champion);
	free(g_vm);

	exit(1);
}
