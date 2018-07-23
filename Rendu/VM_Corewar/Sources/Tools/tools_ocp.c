/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_op.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 22:10:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 14:51:53 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

int		check_ocp_two(int instruct,int cursor)
{
	if ((g_vm->map[instruct] == 9 || g_vm->map[instruct] == 12  ||
		g_vm->map[instruct] == 15) && (g_vm->map[cursor] == 0x80))
			return (0);
	else if ((g_vm->map[instruct] == 10  || g_vm->map[instruct] == 14) &&
			(g_vm->map[cursor] == 0x54 || g_vm->map[cursor] == 0x64 ||
			g_vm->map[cursor] == 0x94 || g_vm->map[cursor] == 0xA4 ||
			g_vm->map[cursor] == 0xD4 || g_vm->map[cursor] == 0xE4))
			return (0);
	else if (g_vm->map[instruct] == 11 &&
			(g_vm->map[cursor] == 0x54 || g_vm->map[cursor] == 0x58 ||
			g_vm->map[cursor] == 0x64 || g_vm->map[cursor] == 0x68 ||
			g_vm->map[cursor] == 0x74 || g_vm->map[cursor] == 0x78))
			return (0);
	else if (g_vm->map[instruct] == 13 &&
			(g_vm->map[cursor] == 0x90 || g_vm->map[cursor] == 0xD0))
			return (0);
	if (g_vm->map[instruct] == 16 && g_vm->map[cursor] == 0x40)
			return (0);
	return (-1);
}

int		check_ocp_one(int instruct,int cursor)
{
	if (g_vm->map[instruct] == 1 &&
			(g_vm->map[cursor] == 0x80))
			return (0);
	else if (g_vm->map[instruct] == 2 &&
			(g_vm->map[cursor] == 0x90 || g_vm->map[cursor] == 0xD0))
			return (0);
	else if (g_vm->map[instruct] == 3 &&
			(g_vm->map[cursor] == 0x50 || g_vm->map[cursor] == 0x70))
			return (0);
	else if ((g_vm->map[instruct] == 4 || g_vm->map[instruct] == 5) &&
			(g_vm->map[cursor] == 0x54))
			return (0);
	else if ((g_vm->map[instruct] == 6 || g_vm->map[instruct] == 7 ||
			g_vm->map[instruct] == 8) &&
			(g_vm->map[cursor] == 0x54 || g_vm->map[cursor] == 0x64 ||
			 g_vm->map[cursor] == 0x74 || g_vm->map[cursor] == 0x94 ||
			 g_vm->map[cursor] == 0xA4 || g_vm->map[cursor] == 0xB4 ||
			 g_vm->map[cursor] == 0xD4 || g_vm->map[cursor] == 0xE4 ||
			 g_vm->map[cursor] == 0xF4 || g_vm->map[cursor] == 0x94))
			return (0);
	return (-1);
}

int		check_ocp(int instruct, int ocp)
{
	int		ret;

	ret = -1;
	if (g_vm->map[instruct] >= 1 && g_vm->map[instruct] <= 8)
		ret = check_ocp_one(instruct, ocp);
	else if (g_vm->map[instruct] >= 9 && g_vm->map[instruct] <= 16)
		ret = check_ocp_two(instruct, ocp);
	return (ret);
}
