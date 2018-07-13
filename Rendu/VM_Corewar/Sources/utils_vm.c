/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:43:36 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:00:21 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

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
	free(list->registers);
	free(list);
}

int		norme_remove(t_process **list, int lives)
{
	lives += (*list)->live;
	(*list)->live = 0;
	(*list) = (*list)->next;
	return (lives);
}

void	decrease_nbr_process(t_process *list)
{
	unsigned int	i;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		if (list->registers[1] == g_vm->champion[i]->num)
		{
			g_vm->champion[i]->nb_process--;
			break;
		}
	}
}

int		process_remove_if_live(t_process **begin_list, int lives)
{
	t_process	*list;
	t_process	*tmp;

	list = *begin_list;
	while (list)
	{
		if (list == *begin_list && list->live == 0)
		{
			*begin_list = (*begin_list)->next;
			decrease_nbr_process(list);
			free_process(list);
			list = *begin_list;
		}
		else if (list->next && list->next->live == 0)
		{
			tmp = list->next->next;
			decrease_nbr_process(list);
			free_process(list->next);
			list->next = tmp;
		}
		else
			norme_remove(&list, lives);
	}
	return (lives);
}

void	introduction(void)
{
	unsigned int i = 0;

	ft_printf("Introducing contestants...\n");
	while (i < g_vm->nb_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				g_vm->champion[i]->num, // num du champion ou ordre ? on laisse un player 0 ou on commence a 1 ?
				g_vm->champion[i]->prog_size,
				g_vm->champion[i]->name,
				g_vm->champion[i]->comment);
		i++;
	}
}

void	print_usage(void)
{
	ft_printf(USE1);
	ft_printf(USE2);
	ft_printf(USE3);
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

int		error_vm(char *s, int c)
{
	unsigned int i;

	i = 0;
	if (!ft_strcmp("open", s))
		ft_printf("Can't read source file %s\n", g_vm->champion[c]->filename);
	else if (!ft_strcmp("size", s))
		ft_printf("Error: File %s has too large a code (%d bytes > %d bytes)\n",
		g_vm->champion[c]->filename, g_vm->champion[c]->prog_size, MEM_SIZE / 6);
	else
		ft_printf(s);
	free_all();
	exit(1);
	return (-1);
}
