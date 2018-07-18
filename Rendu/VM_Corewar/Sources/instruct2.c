/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:01:49 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 19:41:11 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void		ft_live(t_process **proc)
{
	int player;
	unsigned int i;

	i = 0;
	while (i < g_vm->nb_players)
	{
		if ((*proc)->registers[1] == g_vm->champion[i]->num)
			player = (g_vm->champion[i]->num);
		i++;
	}
	if (i != g_vm->nb_players)
	{
		(*proc)->live++;
		g_vm->champion[player]->live++;
	}
}

void		ft_ld(t_process **proc)
{
	int aim;

	aim = (*proc)->registers[0] + (*proc)->fetchqueue[0][1] % IDX_MOD;
	(*proc)->registers[(*proc)->fetchqueue[1][1]] =
		extract(g_vm->map, 4, aim, MEM_SIZE);
}

void		ft_st(t_process **proc)
{
	int aim;

	aim = (*proc)->registers[0] + (*proc)->fetchqueue[1][1] % IDX_MOD;
	if ((*proc)->fetchqueue[1][0] == 1)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->registers[(*proc)->fetchqueue[0][1]];
	else
	{
		g_vm->map[aim] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 6 & 0x3;
		g_vm->map[aim + 1] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 4 & 0x3;
		g_vm->map[aim + 2] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 2 & 0x3;
		g_vm->map[aim + 3] = (*proc)->registers[(*proc)->fetchqueue[1][1]] & 0x3;
	}
}

void		ft_sti(t_process **proc)
{
	int aim;
	int i;

	aim = 0;
	i = 1;
	while (i < 3)
	{
		if ((*proc)->fetchqueue[i][0] == 1)
		{
			aim += (*proc)->registers[(*proc)->fetchqueue[i][1]];
			dprintf(1, "aim += %d\n", (*proc)->registers[(*proc)->fetchqueue[i][1]]);
		}
		else
			aim += (*proc)->fetchqueue[i][1];
		i++;
	}
	dprintf(1, "aim = %d\n", aim);
	g_vm->map[aim] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 6 & 0x3;
	g_vm->map[aim + 1] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 4 & 0x3;
	g_vm->map[aim + 2] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 2 & 0x3;
	g_vm->map[aim + 3] = (*proc)->registers[(*proc)->fetchqueue[1][1]] & 0x3;
}

void		ft_ldi(t_process **proc)
{
	int s;

	s = extract(g_vm->map, IND_SIZE, (*proc)->registers[0] +
			(*proc)->fetchqueue[0][1] % IDX_MOD, MEM_SIZE);
	s += (*proc)->fetchqueue[1][1];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = extract(g_vm->map,
			REG_SIZE, (*proc)->registers[0] + s % IDX_MOD, MEM_SIZE);
	//MODIF CARRY
}
