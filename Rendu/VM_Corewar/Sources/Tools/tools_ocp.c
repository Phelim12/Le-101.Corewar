/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_op.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 22:10:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 18:20:11 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

int		check_ocp_two(int op, int cursor)
{
	int tmp;

	tmp = g_vm->map[cursor];
	if ((op == ZJMP || op == FORK || op == LFORK) && (tmp >> 6 == 0x80 >> 6))
		return (0);
	if ((op == LDI || op == LLDI) &&
		((tmp >> 2) == (0x54 >> 2) || (tmp >> 2) == (0x64 >> 2) ||
		(tmp >> 2) == (0x94 >> 2) || (tmp >> 2) == (0xA4 >> 2) ||
		(tmp >> 2) == (0xD4 >> 2) || (tmp >> 2) == (0xE4 >> 2)))
		return (0);
	if (op == STI &&
		((tmp >> 2) == (0x54 >> 2) || (tmp >> 2) == (0x58 >> 2) ||
		(tmp >> 2) == (0x64 >> 2) || (tmp >> 2) == (0x68 >> 2) ||
		(tmp >> 2) == (0x74 >> 2) || (tmp >> 2) == (0x78 >> 2)))
		return (0);
	if (op == LLD && ((tmp >> 4) == (0x90 >> 4) || (tmp >> 4) == (0xD0 >> 4)))
		return (0);
	if (op == AFF && (tmp >> 6) == (0x40 >> 6))
		return (0);
	return (-1);
}

int		check_ocp_one(int op, int cursor)
{
	int tmp;

	tmp = g_vm->map[cursor];
	if (op == LIVE && ((tmp >> 6) == (0x80 >> 6)))
		return (0);
	if (op == LD && ((tmp >> 4) == (0x90 >> 4) || (tmp >> 4) == (0xD0 >> 4)))
		return (0);
	if (op == ST && ((tmp >> 4) == (0x50 >> 4) || (tmp >> 4) == (0x70 >> 4)))
		return (0);
	if ((op == ADD || op == SUB) && ((tmp >> 2) == (0x54 >> 2)))
		return (0);
	if ((op == AND || op == OR || op == XOR) &&
		((tmp >> 2) == (0x54 >> 2) || (tmp >> 2) == (0x64 >> 2) ||
		(tmp >> 2) == (0x74 >> 2) || (tmp >> 2) == (0x94 >> 2) ||
		(tmp >> 2) == (0xA4 >> 2) || (tmp >> 2) == (0xB4 >> 2) ||
		(tmp >> 2) == (0xD4 >> 2) || (tmp >> 2) == (0xE4 >> 2) ||
		(tmp >> 2) == (0xF4 >> 2) || (tmp >> 2) == (0x94 >> 2)))
		return (0);
	return (-1);
}

int		check_ocp(int op, int cursor)
{
	int		ret;

	ret = -1;
	if (op >= LIVE && op <= XOR)
		ret = check_ocp_one(op, cursor);
	if (op >= ZJMP && op <= AFF)
		ret = check_ocp_two(op, cursor);
	return (ret);
}
