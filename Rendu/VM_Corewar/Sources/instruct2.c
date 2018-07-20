/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:01:49 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 13:44:33 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_live(t_process **proc)
{
	int player;
	unsigned int i;

	dprintf(1, "RUN LIVE Player %d\n", (*proc)->registers[1]);
	i = 0;
	while (i < g_vm->nb_players)
	{
		if (g_vm->champion[i]->num == (*proc)->fetchqueue[0][1])
		{
			player = g_vm->champion[i]->num;
			break ;
		}
		i++;
	}
//	ft_printf("Current proc lives = %d\n", (*proc)->live);
	(*proc)->live++;
//	ft_printf("Current proc lives = %d\n", (*proc)->live);
	if (i < g_vm->nb_players)
	{
		g_vm->champion[player]->live++;
		g_vm->last_live = player;
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
				player, g_vm->champion[player]->name);
	}
/*		int j = -1;
		while (++j < 2)
			ft_printf("Player %d has %d lives\n", j, g_vm->champion[j]->live);
*/}

void		ft_ld(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
//	dprintf(1, "aim = %d\n", aim);
	if ((*proc)->fetchqueue[0][0] == 2)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->fetchqueue[0][1];
	else
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			read_map(aim, REG_SIZE);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[1][1]] ? 1 : 0);
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[1][1], (*proc)->registers[(*proc)->fetchqueue[1][1]]);
}

void		ft_st(t_process **proc)
{
	int		aim;
	unsigned char	*tab;
	int		i;

	i = -1;
	tab = NULL;
	aim = (*proc)->begin + (*proc)->fetchqueue[1][1] % IDX_MOD;
//	dprintf(1, "aim = %d\n", aim);
	if ((*proc)->fetchqueue[1][0] == 1)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->registers[(*proc)->fetchqueue[0][1]];
	else
	{
		tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
		while (++i < 4)
			print((*proc)->registers[1], aim + i, tab[i]);
	}
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[0][1], (*proc)->registers[(*proc)->fetchqueue[0][1]]);
}

void		ft_sti(t_process **proc)
{
	int				fparam;
	int				sparam;
	int				aim;
	unsigned char	*tab;
	int		i;

	i = -1;
	tab = NULL;
	if ((*proc)->fetchqueue[1][0] == 3)
		fparam = read_map((*proc)->fetchqueue[1][1] % IDX_MOD + (*proc)->begin, 4);
	else if ((*proc)->fetchqueue[1][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	else
		fparam = (*proc)->fetchqueue[1][1];
	if ((*proc)->fetchqueue[2][0] == 1)
		sparam = (*proc)->registers[(*proc)->fetchqueue[2][1]];
	else
		sparam = (*proc)->fetchqueue[2][1];
	aim = (fparam + sparam) % IDX_MOD + (*proc)->begin;
	tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
	while (++i < 4)
		print((*proc)->registers[1], aim + i, tab[i]);
//	dprintf(1, "aim = %d\n", aim);
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[0][1], (*proc)->registers[(*proc)->fetchqueue[0][1]]);
}

void		ft_ldi(t_process **proc)
{
	int		fparam;
	int		sparam;

	if ((*proc)->fetchqueue[0][0] == 3)
		fparam = read_map(((*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD), 4);
	else if ((*proc)->fetchqueue[0][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[0][1]];
	else
		fparam = (*proc)->fetchqueue[0][1];
	if ((*proc)->fetchqueue[1][0] == 2)
		sparam = (*proc)->fetchqueue[1][1];
	else
		sparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = read_map(((fparam + sparam)
			% IDX_MOD + (*proc)->begin), 4);
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[2][1], (*proc)->registers[(*proc)->fetchqueue[2][1]]);
}
