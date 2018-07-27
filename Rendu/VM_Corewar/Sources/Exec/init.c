/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 17:33:45 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 20:08:59 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

void		init_vm(char const **argv)
{
	void	*tmp;

	if ((tmp = (t_vm*)malloc(sizeof(t_vm))))
		g_vm = tmp;
	else
		error_vm("malloc failed in init_vm\n", 0);
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->cycle = 1;
	g_vm->checks = 0;
	g_vm->champion = NULL;
	g_vm->list_process = NULL;
	g_vm->map = NULL;
	g_vm->p_map = NULL;
	g_vm->last_live = -1;
	g_vm->dump = 0;
	g_vm->v = 0;
	g_vm->d_size = 0;
	g_vm->d_cycles = 0;
	g_vm->nb_players = 0;
	g_vm->nb_proc = 0;
	g_vm->nb_live = 0;
	init_champs(argv);
	init_map();
}

int			init_map(void)
{
	t_process		*list_tmp;
	int				*tmp;
	unsigned int	i;

	i = 0;
	g_vm->map = malloc(MEM_SIZE + 1);
	if (!g_vm->map || !(g_vm->p_map = malloc(MEM_SIZE + 1)))
		error_vm("malloc failed in init_map\n", 0);
	g_vm->map[MEM_SIZE] = '\0';
	g_vm->p_map[MEM_SIZE] = '\0';
	g_vm->map = ft_memset(g_vm->map, 0, (size_t)MEM_SIZE);
	g_vm->p_map = ft_memset(g_vm->p_map, 0, (size_t)MEM_SIZE);
	list_tmp = g_vm->list_process;
	while (list_tmp)
	{
		tmp = list_tmp->reg;
		ft_memcpy(&g_vm->map[tmp[0]],
				g_vm->champion[i]->instructions, g_vm->champion[i]->prog_size);
		ft_memset(&g_vm->p_map[tmp[0]],
				tmp[1], g_vm->champion[i]->prog_size);
		list_tmp = list_tmp->next;
		i++;
	}
	return (0);
}

int			init_process(unsigned int a)
{
	g_vm = NULL;
	if (!(g_vm = (t_vm*)malloc(sizeof(t_vm))))
		error_vm("malloc failed in init_vm\n", 0);
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->cycle = 1;
	g_vm->checks = 0;
	g_vm->champion = NULL;
	g_vm->list_process = NULL;
	g_vm->map = NULL;
	g_vm->p_map = NULL;
	g_vm->last_live = -1;
	g_vm->dump = 0;
	g_vm->v = 0;
	g_vm->d_size = 0;
	g_vm->d_cycles = 0;
	g_vm->nb_players = 0;
	g_vm->nb_proc = 0;
	g_vm->nb_live = 0;
	init_champs(argv);
	init_map();
}
