/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 16:59:52 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 16:30:47 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int				get_reg(int cursor)
{
	return (g_vm->map[cursor]);
}

int				get_dir(int cursor, t_op instruction)
{
	int		ret;
	int		j;
	int		size;

	size = (instruction.size_dir == 1 ? 2 : 4);
	j = 0;
	ret = g_vm->map[cursor];
	while (j < size - 1)
	{
		ret = (ret << 8) | g_vm->map[cursor + j + 1];
		j++;
	}
	return ((size == 2 ? (short)ret : ret));
}

int				get_ind(int cursor)
{
	return (g_vm->map[cursor] << 8 | g_vm->map[cursor + 1]);
}
