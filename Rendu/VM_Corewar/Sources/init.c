/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 17:33:45 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 11:30:08 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int		init_process(unsigned int a)
{
	int			*tmp;
	t_list		*new;

	if (!(tmp = (int*)malloc(REG_SIZE * REG_NUMBER + 1)))
		return (-1);
	else
	{
		ft_memset(tmp, 0, REG_NUMBER + 1);
		tmp[1] = g_vm->champion[a]->num;
		tmp[0] = tmp[1] * MEM_SIZE / g_vm->nb_players;
		ft_printf("num : %i\n", tmp[1]);
		new = ft_lstnew(tmp, REG_SIZE * REG_NUMBER);
		if (g_vm->list_process == NULL)
			g_vm->list_process = new;
		else
		{
			ft_lstadd(&new, g_vm->list_process);
			g_vm->list_process = new;
		}
		free(tmp);
	}
	return (0);
}

int		init_fetchqueue(unsigned int a)
{
	unsigned char	*tmp;
	t_list			*new;

	if (!(tmp = (unsigned char*)malloc(64 + 2)))
		return (-1);
	else
	{
		ft_memset(tmp, 0, 64 + 2);
		new = ft_lstnew(tmp, 64 + 2);
		if (g_vm->fetchqueue == NULL)
			g_vm->fetchqueue = new;
		else
		{
			ft_lstadd(&new, g_vm->fetchqueue);
			g_vm->fetchqueue = new;
		}
		free(tmp);
	}
	return (0);
}


static int	sub2_init_champ(void) //peut etre a passer en return INT pour la remontee d'erreur
{
	/*	void			*tmp;
		unsigned int	a;

		a = -1;
		if ((tmp = (int**)malloc(sizeof(int*) * g_vm->champion[i]->nb_process)))
		g_vm->champion[i]->registers = tmp;
		while (++a < g_vm->champion[i]->nb_process)
		{
		if ((tmp = (int*)malloc(REG_SIZE * (REG_NUMBER + 1))))
		g_vm->champion[i]->registers[a] = tmp;
		ft_memset(g_vm->champion[i]->registers[a], 0, REG_NUMBER + 1);
		if ((tmp = (unsigned char*)malloc(16)))
		g_vm->champion[i]->fetchqueue[a] = tmp;
		ft_memset(g_vm->champion[i]->fetchqueue[a], 0, 16);
		g_vm->champion[i]->registers[a][1] = g_vm->champion[i]->num;
		g_vm->champion[i]->registers[a][0] = g_vm->champion[i]->num * MEM_SIZE
		/ g_vm->nb_players;
		}*/
	unsigned int	a;

	a = -1;
	while (++a < g_vm->nb_players)
	{
		if (init_process(a) == - 1 || init_fetchqueue(a) == -1 ||
				get_champ(a) == -1)
			return (-1);
	}
	return (0);
}

static void	sub_init_champ(void)
{
	unsigned int	i;
	unsigned int	num;
	unsigned int	j;
	int				f;

	i = -1;
	while (++i < g_vm->nb_players)
	{
		g_vm->champion[i]->live = 0;
		g_vm->champion[i]->nb_process = 1;
		num = 0;
		while (g_vm->champion[i]->num == -1)
		{
			j = -1;
			f = 1;
			while (++j < g_vm->nb_players)
				if ((long)g_vm->champion[j]->num == (long)num)
					f = 0;
			if (f == 0)
				num++;
			else
				g_vm->champion[i]->num = num;
		}
	}
	sub2_init_champ();
}

void		init_champs(char const **argv)
{
	void			*tmp;
	unsigned int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_strcmp(".cor", &argv[i][ft_strlen(argv[i]) - 4]))
			g_vm->nb_players++;
		i++;
	}
	i = 0;
	if ((tmp = (t_champ**)malloc(sizeof(t_champ*) * g_vm->nb_players + 1)))
		g_vm->champion = tmp;
	while (i < g_vm->nb_players)
	{
		if ((tmp = (t_champ*)malloc(sizeof(t_champ))))
			g_vm->champion[i] = tmp;
		g_vm->champion[i++]->num = -1;
	}
	if (g_vm->nb_players > MAX_PLAYERS)
		ft_error("Too many .cor files in parameters\n", 0);
	parse_args(argv);
	sub_init_champ();
}

int			init_map(void)
{
	t_list			*list_tmp;
	int				*tmp;
	unsigned int	i;

	i = 0;
	if (!(g_vm->map = malloc(MEM_SIZE + 1)))
		return (-1);
	g_vm->map[MEM_SIZE] = '\0';
	g_vm->map = ft_memset(g_vm->map, 0, (size_t)MEM_SIZE);
	list_tmp = g_vm->list_process;
	while (list_tmp)
	{
		tmp = list_tmp->content;
		ft_memcpy(&g_vm->map[tmp[0]],
				g_vm->champion[i]->instructions, g_vm->champion[i]->prog_size);
		list_tmp = list_tmp->next;
		i++;
	}
	return (0);
}

void		init_vm(char const **argv)
{
	void	*tmp;

	if ((tmp = (t_vm*)malloc(sizeof(t_vm))))
		g_vm = tmp;
	g_vm->dump = 0;
	g_vm->d_cycles = 0;
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->cycle = 0;
	g_vm->nb_players = 0;
	g_vm->list_process = NULL;
	g_vm->fetchqueue = NULL;
	init_champs(argv);
	init_map(); //full 0, map de MEM_SIZE, init nb_players * NB_REG registres
	//	load_champs(); //divide map in nb_players and load them -> need to interpret .cor files
}
