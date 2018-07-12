/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 16:59:52 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 10:58:20 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

t_op			get_reg(int cursor, t_op instruction, int i)
{
	instruction.params[i] = g_vm->map[cursor];
	return (instruction);
}

t_op			get_dir(int cursor, t_op instruction, int i)
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
	instruction.params[i] = ret;
	return (instruction);
}

t_op			get_ind(int cursor, t_op instruction, int i)
{
	instruction.params[i] = g_vm->map[cursor] << 8 | g_vm->map[cursor + 1];
	return (instruction);
}
