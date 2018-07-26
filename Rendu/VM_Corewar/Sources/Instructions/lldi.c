/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lldi.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 13:59:42 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:22:11 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_lldi(t_process **proc, int fparam, int sparam)
{
	dprintf(1, "1st param = %d, sparam = %d, pc = %d\n",
			fparam, sparam, (*proc)->begin);
	dprintf(1, "register[%d] = %d\n",
			(*proc)->params[2][1],
			(*proc)->registers[(*proc)->params[2][1]]);
}

void		ft_lldi(t_process **proc)
{
	int				fparam;
	int				sparam;

	if ((*proc)->params[0][0] == 3)
		fparam =
			read_map(((*proc)->begin + (*proc)->params[0][1] % IDX_MOD), 4);
	else if ((*proc)->params[0][0] == 1)
		fparam = (*proc)->registers[(*proc)->params[0][1]];
	else
		fparam = (*proc)->params[0][1];
	if ((*proc)->params[1][0] == 2)
		sparam = (*proc)->params[1][1];
	else
		sparam = (*proc)->registers[(*proc)->params[1][1]];
	(*proc)->registers[(*proc)->params[2][1]] =
		read_map((fparam + sparam + (*proc)->begin), 4);
	(*proc)->carry = (!(*proc)->registers[(*proc)->params[2][1]] ? 1 : 0);
//	debug_lldi(proc, fparam, sparam);
}
