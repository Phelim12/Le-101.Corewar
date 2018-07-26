/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 01:59:29 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_sti(t_process **proc, int aim, int debug)
{
	if (debug == 1)
	{
		dprintf(2, "sti PC = %d\n", PROC->reg[0]);
		dprintf(2, "sti params : %d & %d\n",
				PROC->params[1][1], PROC->params[2][1]);
		dprintf(2, "sti register[%d] = %d\n",
				PROC->params[0][1],
				PROC->reg[PROC->params[0][1]]);
	}
	else if (debug == 2)
	{
		dprintf(2, "sti aim = %d\n", aim);
		dprintf(1, "register[%d] = %d\n",
				PROC->params[0][1],
				PROC->reg[PROC->params[0][1]]);
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
		dprintf(2, "params type = %d | value = %d\n", PROC->params[i][0], PROC->params[i][1]);
		dprintf(2, "register %d value = %d\n", i, PROC->reg[PROC->params[i][1]]);
	}*/
//	dprintf(2, "param = %d\n", PROC->params[1][1]);
//	dprintf(2, "param  modulo 'IDX_MOD' = %d\n", PROC->params[1][1] % IDX_MOD);
//	dprintf(2, "read  = %d\n", read_map(PROC->params[1][1] % IDX_MOD + PROC->begin, 4));
	if (PROC->params[1][0] == 3)
		fparam = read_map(PROC->params[1][1] % IDX_MOD + PROC->begin, 4);
	else if (PROC->params[1][0] == 1)
		fparam = PROC->reg[PROC->params[1][1]];
	else if (PROC->params[1][0] == 2)
		fparam = PROC->params[1][1];
	if (PROC->params[2][0] == 1)
		sparam = PROC->reg[PROC->params[2][1]];
	else
		sparam = PROC->params[2][1];
//	dprintf(2, "fparam = %d, aim = %d\n", fparam, aim);
	if ((aim = (fparam + sparam) % IDX_MOD + PROC->begin) < 0)
		aim += MEM_SIZE;
	tab = itoo(PROC->reg[PROC->params[0][1]]);
	i = -1;
	while (++i < 4)
		print(PROC->reg[1], (aim + i) % MEM_SIZE, tab[i]);
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
