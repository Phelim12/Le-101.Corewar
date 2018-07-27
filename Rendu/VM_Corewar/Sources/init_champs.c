/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 02:36:04 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 03:16:20 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static void		sort_champ_tab(void)
{
	t_champ			*tmp;
	unsigned int	i;
	int				a;

	a = g_vm->nb_players;
	i = -1;
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
		if (init_process(a) == -1 || get_champ(a) == -1)
			error_vm("malloc failed\n", 0);
}

static void		init_champ_num(void)
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

void			init_champs(char const **argv)
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
		g_vm->champion[i++]->num = 0;
	}
	if (g_vm->nb_players > MAX_PLAYERS)
		error_vm("Too many .cor files in parameters\n", 0);
	parse_args(argv);
	init_champ_num();
}
