/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct1.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 17:57:30 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 15:44:42 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"


void		ft_lld(t_process **proc)
{

	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
	if ((*proc)->fetchqueue[0][0] == 2)
		(*proc)->registers[(*proc)->fetchqueue[1][1]] = (*proc)->fetchqueue[0][1];
	else
		(*proc)->registers[(*proc)->fetchqueue[1][1]] =
			read_map(aim, REG_SIZE);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[1][1]] ? 1 : 0);
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[1][1], (*proc)->registers[(*proc)->fetchqueue[1][1]]);
}

void		ft_lldi(t_process **proc)
{

	int				fparam;
	int				sparam;

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
//	dprintf(1, "1st param = %d, sparam = %d, pc = %d\n", fparam, sparam, (*proc)->begin);
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = read_map((fparam + sparam + (*proc)->begin), 4);
	(*proc)->carry = (!(*proc)->registers[(*proc)->fetchqueue[2][1]] ? 1 : 0);
//	dprintf(1, "register[%d] = %d\n", (*proc)->fetchqueue[2][1], (*proc)->registers[(*proc)->fetchqueue[2][1]]);
}

void		ft_zjmp(t_process **proc)
{
	if ((*proc)->carry == 1)
		(*proc)->registers[0] = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
}

void		ft_aff(t_process **proc)
{
	char c;

	c = (*proc)->registers[(*proc)->fetchqueue[0][1]] % 256;
	if (c < 32 || c > 126)
		return ;
	// ft_printf("%c\n", c);
}

void		ft_fork(t_process **proc, t_process **begin)
{
	int				aim;
	t_process		*new;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
	dprintf(1, "aim = %d\n", aim);
	new = lstnew_vm((*proc)->registers, REG_SIZE * REG_NUMBER);
	new->registers[0] = aim;
	lstadd_vm(begin, new);
}
