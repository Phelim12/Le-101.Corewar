/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:51:55 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_sti(t_process **proc, int aim, int debug)
{
	if (debug == 1)
	{
		dprintf(2, "sti PC = %d\n", (*proc)->registers[0]);
		dprintf(2, "sti params : %d & %d\n",
				(*proc)->fetchqueue[1][1], (*proc)->fetchqueue[2][1]);
		dprintf(2, "sti register[%d] = %d\n",
				(*proc)->fetchqueue[0][1],
				(*proc)->registers[(*proc)->fetchqueue[0][1]]);
	}
	else if (debug == 2)
	{
		dprintf(2, "sti aim = %d\n", aim);
		dprintf(1, "register[%d] = %d\n",
				(*proc)->fetchqueue[0][1],
				(*proc)->registers[(*proc)->fetchqueue[0][1]]);
	}
}

void		ft_sti(t_process **proc)
{
	int				fparam;
	int				sparam;
	int				aim;
	unsigned char	*tab;
	int				i;

//	debug_sti(proc, 0, 1);
	i = -1;
	tab = NULL;
	/*while (++i < 3)
	{
		dprintf(2, "params type = %d | value = %d\n", (*proc)->fetchqueue[i][0], (*proc)->fetchqueue[i][1]);
		dprintf(2, "register %d value = %d\n", i, (*proc)->registers[(*proc)->fetchqueue[i][1]]);
	}*/
//	dprintf(2, "param = %d\n", (*proc)->fetchqueue[1][1]);
//	dprintf(2, "param  modulo 'IDX_MOD' = %d\n", (*proc)->fetchqueue[1][1] % IDX_MOD);
//	dprintf(2, "read  = %d\n", read_map((*proc)->fetchqueue[1][1] % IDX_MOD + (*proc)->begin, 4));
	if ((*proc)->fetchqueue[1][0] == 3)
		fparam = read_map((*proc)->fetchqueue[1][1] % IDX_MOD + (*proc)->begin, 4);
	else if ((*proc)->fetchqueue[1][0] == 1)
		fparam = (*proc)->registers[(*proc)->fetchqueue[1][1]];
	else if ((*proc)->fetchqueue[1][0] == 2)
		fparam = (*proc)->fetchqueue[1][1];
	if ((*proc)->fetchqueue[2][0] == 1)
		sparam = (*proc)->registers[(*proc)->fetchqueue[2][1]];
	else
		sparam = (*proc)->fetchqueue[2][1];
//	dprintf(2, "fparam = %d, aim = %d\n", fparam, aim);
	if ((aim = (fparam + sparam) % IDX_MOD + (*proc)->begin) < 0)
		aim += MEM_SIZE;
	tab = itoo((*proc)->registers[(*proc)->fetchqueue[0][1]]);
	i = -1;
	while (++i < 4)
		print((*proc)->registers[1], (aim + i) % MEM_SIZE, tab[i]);
//	debug_sti(proc, aim, 2);
}



// P1 ld	%0, r3				PC -> 0		Cycle 4
// P1 live	42					PC -> 7		Cycle 14
// P1 sti	r15, %0, r14		PC -> 12		Cycle 39
// P1 live	42					PC -> 18		Cycle 49
// P1 sti	r15, %0, r14		PC -> 23		Cycle 74
// P1 live	42					PC -> 29		Cycle 84
// P1 sti	r15, %0, r14		PC -> 34		Cycle 109
// P1 live	42					PC -> 40		Cycle 119
// P1 sti	r15, %0, r14		PC -> 45		Cycle 144
// P1 sti	r15, %0, r14		PC -> 51		Cycle 169
// P1 sti	r15, %0, r14		PC -> 57		Cycle 194
// P1 sti	r1, %-74, %1		PC -> 63		Cycle 219
// # R_CORWAR
// P1 ld 0 r3
// P1 live 42
// P1 sti r15 0 0
// P1 live 42
// P1 sti r15 0 0
// P1 live 42
// P1 sti r15 0 0
// P1 live 42
// P1 sti r15 0 0
// P1 sti r15 0 0
// P1 sti r15 0 0
// P1 sti r1 -74 1
