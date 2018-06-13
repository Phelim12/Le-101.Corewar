/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 17:33:45 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 16:50:28 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

static void	sub2_init_champ(int i) //peut etre a passer en return INT pour la remontee d'erreur
{
	void			*tmp;
	unsigned int	a;

	a = -1;
	if ((tmp = (int**)malloc(sizeof(int*) * g_vm->champion[i]->nb_process)))
		g_vm->champion[i]->registers = tmp;
	while (++a < g_vm->champion[i]->nb_process)
	{
		if ((tmp = (int*)malloc(REG_SIZE * REG_NUMBER + 1)))
			g_vm->champion[i]->registers[a] = tmp;
		ft_memset(g_vm->champion[i]->registers[a], 0, REG_NUMBER + 1);
		g_vm->champion[i]->registers[a][1] = g_vm->champion[i]->num;
	}
	if (get_champ(i, g_vm->champion[i]->filename) == -1)
		return ;
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
		sub2_init_champ(i);
	}
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
		ft_error("Too many .cor files in parameters\n");
	parse_args(argv);
	sub_init_champ();
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
	init_champs(argv);
	//init_map(); //full 0, map de MEM_SIZE, init nb_players * NB_REG registres
//	load_champs(); //divide map in nb_players and load them -> need to interpret .cor files
}
