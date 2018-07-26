/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sti.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:26:27 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 01:38:20 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_sti(t_process **proc)
{
	int				fparam;
	int				sparam;
	unsigned char	*tab;
	int				aim;
	int				var;

	fparam = 0;
	sparam = 0;
	var = -1;
	tab = NULL;
	if (PROC->params[1][0] == 3)
		fparam = read_map(PROC->params[1][1] % IDX_MOD + PROC->begin);
	else if (PROC->params[1][0] == 1)
		fparam = PROC->reg[PROC->params[1][1]];
	else if (PROC->params[1][0] == 2)
		fparam = PROC->params[1][1];
	if (PROC->params[2][0] == 1)
		sparam = PROC->reg[PROC->params[2][1]];
	else
		sparam = PROC->params[2][1];
	if ((aim = (fparam + sparam) % IDX_MOD + PROC->begin) < 0)
		aim += MEM_SIZE;
	tab = itoo(PROC->reg[PROC->params[0][1]]);
	while (++var < 4)
		print(PROC->reg[1], (aim + var) % MEM_SIZE, tab[var]);
}
