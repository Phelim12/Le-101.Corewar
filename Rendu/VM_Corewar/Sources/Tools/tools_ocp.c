/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_op.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 22:10:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 22:58:56 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

int		check_ocp_two(int op,int cursor)
{
	if ((op == 9 || op == 12  ||
		op == 15) && ((g_vm->map[cursor] >> 2) == (0x80 >> 2)))
			return (0);
	else if ((op == 10  || op == 14) &&
			((g_vm->map[cursor] >> 2) == (0x54 >> 2) || (g_vm->map[cursor] >> 2) == (0x64 >> 2) ||
			(g_vm->map[cursor] >> 2) == (0x94 >> 2) || (g_vm->map[cursor] >> 2) == (0xA4 >> 2) ||
			(g_vm->map[cursor] >> 2) == (0xD4 >> 2) || (g_vm->map[cursor] >> 2) == (0xE4 >> 2)))
			return (0);
	else if (op == 11 &&
			((g_vm->map[cursor] >> 2) == (0x54 >> 2) || (g_vm->map[cursor] >> 2) == (0x58 >> 2) ||
			(g_vm->map[cursor] >> 2) == (0x64 >> 2) || (g_vm->map[cursor] >> 2) == (0x68 >> 2) ||
			(g_vm->map[cursor] >> 2) == (0x74 >> 2) || (g_vm->map[cursor] >> 2) == (0x78 >> 2)))
			return (0);
	else if (op == 13 &&
			((g_vm->map[cursor] >> 2) == (0x90 >> 2) || (g_vm->map[cursor] >> 2) == (0xD0 >> 2)))
			return (0);
	if (op == 16 && (g_vm->map[cursor] >> 2) == (0x40 >> 2))
			return (0);
	return (-1);
}

int		check_ocp_one(int op,int cursor)
{
	if (op == 1 &&
			((g_vm->map[cursor] >> 2) == (0x80 >> 2)))
			return (0);
	else if (op == 2 &&
			((g_vm->map[cursor] >> 2) == (0x90 >> 2) || (g_vm->map[cursor] >> 2) == (0xD0 >> 2)))
			return (0);
	else if (op == 3 &&
			((g_vm->map[cursor] >> 2) == (0x50 >> 2) || (g_vm->map[cursor] >> 2) == (0x70 >> 2)))
			return (0);
	else if ((op == 4 || op == 5) &&
			((g_vm->map[cursor] >> 2) == (0x54 >> 2)))
			return (0);
	else if ((op == 6 || op == 7 ||
			op == 8) &&
			((g_vm->map[cursor] >> 2) == (0x54 >> 2) || (g_vm->map[cursor] >> 2) == (0x64 >> 2) ||
			 (g_vm->map[cursor] >> 2) == (0x74 >> 2) || (g_vm->map[cursor] >> 2) == (0x94 >> 2) ||
			 (g_vm->map[cursor] >> 2) == (0xA4 >> 2) || (g_vm->map[cursor] >> 2) == (0xB4 >> 2) ||
			 (g_vm->map[cursor] >> 2) == (0xD4 >> 2) || (g_vm->map[cursor] >> 2) == (0xE4 >> 2) ||
			 (g_vm->map[cursor] >> 2) == (0xF4 >> 2) || (g_vm->map[cursor] >> 2) == (0x94 >> 2)))
			return (0);
	return (-1);
}

int		check_ocp(int op, int ocp)
{
	int		ret;

	ret = -1;
	if (op >= 1 && op <= 8)
		ret = check_ocp_one(op, ocp);
	else if (op >= 9 && op <= 16)
		ret = check_ocp_two(op, ocp);
	return (ret);
}
/*
P2 | ld 0 r2
P1 | ld 50595074 r3
P1 | ld 67293184 r4
P1 | ld 0 r5
P1 | st r1 6
P2 | zjmp 510 OK
P1 | live -1
P2 | zjmp 123 OK
P2 | ld 57672449 r4
P2 | ld -16186886 r5
P1 | sti r5 0 50595074
P2 | ld 151087104 r3
P2 | ld 0 r2
P1 | add r3 r4 r5
P2 | st r4 511
P1 | ld 0 r16
P2 | st r5 510
P1 | zjmp -22 OK
P2 | zjmp 501 OK
P2 | st r3 511
P1 | live -1
P2 | zjmp 506 OK
P1 | sti r5 117888258 50595074
P1 | and 84054016 117888258 r2
P2 | zjmp 360 OK
*/

/*
P1 |	ld			Cycle 4
P2 |	ld			Cycle 4
P1 |	ld			Cycle 9
P1 |	ld			Cycle 14
P1 |	st			Cycle 19
P2 |	zjmp		Cycle 24
P1 |	live		Cycle 29
P2 |	zjmp		Cycle 44
P2 |	ld			Cycle 49
P2 |	ld			Cycle 54
P1 |	sti			Cycle 54
P2 |	ld			Cycle 59
P2 |	ld			Cycle 64
P1 |	add			Cycle 64
P2 |	st			Cycle 69
P1 |	ld			Cycle 69
P2 |	st			Cycle 74
P1 |	zjmp		Cycle 89
P2 |	zjmp		Cycle 94
P2 |	st			Cycle 99
P1 |	live		Cycle 99
P2 |	zjmp		Cycle 119
P1 |	sti			Cycle 124
P2 |	zjmp		Cycle 139
P2 |	ld			Cycle 163
P2 |	st			Cycle 168
*/
