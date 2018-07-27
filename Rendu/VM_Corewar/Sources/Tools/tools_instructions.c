/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_instructions.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:47:49 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 19:16:22 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

unsigned char		*itoo(int nb)
{
	unsigned char	*tab;

	tab = malloc(sizeof(unsigned char) * 4);
	tab[0] = (nb & 0xFF000000) >> 24;
	tab[1] = (nb & 0xFF0000) >> 16;
	tab[2] = (nb & 0xFF00) >> 8;
	tab[3] = (nb & 0xFF);
	return (tab);
}

int					read_map(int index)
{
	int	ret;

	ret = 0;
	index %= MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
	ret += g_vm->map[index % MEM_SIZE] << 24;
	ret += g_vm->map[(index + 1) % MEM_SIZE] << 16;
	ret += g_vm->map[(index + 2) % MEM_SIZE] << 8;
	ret += g_vm->map[(index + 3) % MEM_SIZE];
	return (ret);
}

int					check_reg(t_process *proc)
{
	t_op	info;
	int		i;

	i = -1;
	info = get_opcode(proc->op);
	while (++i < info.nparams)
		if ((proc->params[i][0] == REG_CODE) &&
			(proc->params[i][1] < MIN_REG || proc->params[i][1] > MAX_REG))
			return (0);
	return (1);
}
