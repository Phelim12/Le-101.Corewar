/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 18:01:49 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 13:41:42 by jjanin-r    ###    #+. /#+    ###.fr     */
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
		if ((*proc)->registers[1] == (*proc)->fetchqueue[0][1])
			player = (*proc)->registers[1];
		i++;
	}
	if (i <= g_vm->nb_players)
	{
		(*proc)->live++;
		g_vm->champion[player]->live++;
		g_vm->last_live = player;
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
				player, g_vm->champion[player]->name);
	}
}

void		ft_ld(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
	dprintf(1, "aim = %d\n", aim);
	if ((*proc)->fetchqueue[0][0] == 2)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->fetchqueue[0][1];
	else
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			extract(g_vm->map, REG_SIZE, aim, MEM_SIZE);
	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[1][1], (*proc)->registers[(*proc)->fetchqueue[1][1]]);
}

void		ft_st(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[1][1] % IDX_MOD;
	if ((*proc)->fetchqueue[1][0] == 1)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->registers[(*proc)->fetchqueue[0][1]];
/*	else
	{
		g_vm->map[aim] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 6 & 0x3;
		g_vm->map[aim + 1] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 4 & 0x3;
		g_vm->map[aim + 2] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 2 & 0x3;
		g_vm->map[aim + 3] = (*proc)->registers[(*proc)->fetchqueue[1][1]] & 0x3;
	}
*/	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[1][1], (*proc)->registers[(*proc)->fetchqueue[1][1]]);
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
/*	g_vm->map[aim] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 6 & 0x3;
	g_vm->map[aim + 1] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 4 & 0x3;
	g_vm->map[aim + 2] = (*proc)->registers[(*proc)->fetchqueue[1][1]] >> 2 & 0x3;
	g_vm->map[aim + 3] = (*proc)->registers[(*proc)->fetchqueue[1][1]] & 0x3;
*/}

void		ft_ldi(t_process **proc)
{
	int s;

	s = extract(g_vm->map, IND_SIZE, (*proc)->registers[0] +
			(*proc)->fetchqueue[0][1] % IDX_MOD, MEM_SIZE);
	if ((*proc)->fetchqueue[1][0] == 2)
		s += (*proc)->fetchqueue[1][1];
	else
		s+= (*proc)->registers[(*proc)->fetchqueue[1][1]];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = extract(g_vm->map,
			REG_SIZE, (*proc)->registers[0] + s % IDX_MOD, MEM_SIZE);
	modify_carry(proc);
}
