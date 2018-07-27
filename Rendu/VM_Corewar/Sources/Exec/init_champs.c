/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 18:14:53 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 18:40:44 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		sort_champ_tab(void)
{
	t_champ			*tmp;
	unsigned int	i;
	int				a;

	i = -1;
	a = g_vm->nb_players;
	while (++i < g_vm->nb_players - 1)
	{
		if (g_vm->champion[i]->num < g_vm->champion[i + 1]->num)
		{
			tmp = g_vm->champion[i];
			g_vm->champion[i] = g_vm->champion[i + 1];
			g_vm->champion[i + 1] = tmp;
			i = -1;
		}
	}
	while (--a >= 0)
	{
		init_process(a);
		read_champ(a);
	}
}

void		init_champ_num(void)
{
	unsigned int	i;
	long			num;
	unsigned int	j;

	i = -1;
	num = 1;
	while (++i < g_vm->nb_players)
	{
		num = 1;
		g_vm->champion[i]->live = 0;
		if (g_vm->champion[i]->num == 0)
		{
			j = -1;
			while (++j < g_vm->nb_players)
			{
				if (g_vm->champion[j]->num == num)
				{
					num++;
					j = -1;
				}
			}
			g_vm->champion[i]->num = num;
		}
	}
	sort_champ_tab();
}

void		init_champs(char const **argv)
{
	unsigned int	i;

	i = -1;
	while (argv[++i])
		if (!ft_strcmp(".cor", &argv[i][ft_strlen(argv[i]) - 4]))
			g_vm->nb_players++;
	i = -1;
	g_vm->champion = (t_champ**)malloc(sizeof(t_champ*) * g_vm->nb_players + 1);
	if (!g_vm->champion)
		error_vm("malloc failed in init_champs\n", 0);
	while (++i < g_vm->nb_players)
	{
		g_vm->champion[i] = (t_champ*)malloc(sizeof(t_champ));
		if (!g_vm->champion[i])
			error_vm("malloc failed in init_champs\n", 0);
		g_vm->champion[i]->name = NULL;
		g_vm->champion[i]->comment = NULL;
		g_vm->champion[i]->filename = NULL;
		g_vm->champion[i]->instructions = NULL;
		g_vm->champion[i]->num = 0;
	}
	if (g_vm->nb_players > MAX_PLAYERS)
		error_vm("Too many .cor files in parameters\n", 0);
	parse_args(argv);
	init_champ_num();
}
