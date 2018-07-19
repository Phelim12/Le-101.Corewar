/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instruct1.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 17:57:30 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 13:42:41 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

// manque la gestion des labels

void		ft_lld(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1];
	(*proc)->registers[(*proc)->fetchqueue[1][1]] =
		extract(g_vm->map, 4, aim, MEM_SIZE);
	modify_carry(proc);
}

void		ft_lldi(t_process **proc)
{
	int s;

	s = extract(g_vm->map, IND_SIZE, (*proc)->begin +
			(*proc)->fetchqueue[0][1], MEM_SIZE);
	s += (*proc)->fetchqueue[1][1];
	(*proc)->registers[(*proc)->fetchqueue[2][1]] = extract(g_vm->map,
			REG_SIZE, (*proc)->begin + s, MEM_SIZE);
	modify_carry(proc);
}

void		ft_zjmp(t_process **proc)
{
//	(*proc)->carry = 1;
	if ((*proc)->carry == 1)
		(*proc)->registers[0] = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
}

void		ft_aff(t_process **proc)
{
	char c;

	c = (*proc)->registers[(*proc)->fetchqueue[0][1]];
	ft_printf("%c\n", c);
}

void		ft_fork(t_process **proc)
{
	int aim;

	aim = (*proc)->begin + (*proc)->fetchqueue[0][1] % IDX_MOD;
	//creer une copie du process a g_vm->map[aim];
}
