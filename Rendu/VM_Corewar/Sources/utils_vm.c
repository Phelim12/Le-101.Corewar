/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:43:36 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 12:37:00 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

/*
**fonction de liste a tester
*/
void	free_list(t_list *list)
{
}

void	list_remove_if(t_list **begin_list, void *content_ref, int (*cmp)())
{
	t_list	*list;
	t_list	*tmp;

	list = *begin_list;
	while (list && list->next)
	{
		if (list == *begin_list && cmp(list->content, content_ref) == 0)
		{
			*begin_list = (*begin_list)->next;
			free_list(list);
			list = *begin_list;
		}
		else if (cmp(list->next->content, content_ref) == 0)
		{
			tmp = list->next->next;
			free(list->next);
			list->next = tmp;
		}
		else
			list = list->next;
	}
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
