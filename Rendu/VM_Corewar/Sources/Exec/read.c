/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 16:59:52 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 04:04:06 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int				read_reg(int cursor)
{
	return (g_vm->map[cursor]);
}

int				read_ind(int cursor)
{
	return (g_vm->map[cursor] << 8 | g_vm->map[(cursor + 1) % MEM_SIZE]);
}

int				read_ocp(int cursor, t_op instruction, t_process **proc)
{
	PROC->params[0][0] = g_vm->map[cursor] >> 6 & 0x3;
	PROC->params[1][0] = g_vm->map[cursor] >> 4 & 0x3;
	PROC->params[2][0] = g_vm->map[cursor] >> 2 & 0x3;
	PROC->params[3][0] = g_vm->map[cursor] & 0x3;
	if (check_ocp(PROC->op, cursor))
		PROC->op = -1;
	return (read_params(++cursor % MEM_SIZE, instruction, proc));
}

void			read_instruction(t_process **proc)
{
	t_op	instruction;
	int		cursor;

	cursor = PROC->reg[0];
	instruction = get_opcode(PROC->op);
	if (instruction.info_params)
		PROC->reg[0] = read_ocp(++cursor % MEM_SIZE, instruction, proc) %
			MEM_SIZE;
	else
		PROC->reg[0] = read_params(++cursor % MEM_SIZE, instruction, proc) %
			MEM_SIZE;
}

int				read_dir(int cursor, t_op instruction)
{
	int		ret;
	int		j;
	int		size;

	size = (instruction.size_dir == 1 ? 2 : 4);
	j = 0;
	ret = g_vm->map[cursor];
	while (j < size - 1)
	{
		ret = (ret << 8) | g_vm->map[(cursor + j + 1) % MEM_SIZE];
		j++;
	}
	return ((size == 2 ? (short)ret : ret));
}
