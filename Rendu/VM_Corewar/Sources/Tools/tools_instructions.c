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

int					read_map(int index, int size)
{
	int					i;
	int					ret;

//	dprintf(2, "index read_map = %d\n", index);
	i = 0;
	ret = 0;
	index %= MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
//	dprintf(2, "index read_map = %d\n", index);
//	dprintf(2, "index + i mod MEM_SIZE = %d\n", index + i % MEM_SIZE);
	ret += g_vm->map[(index + i) % MEM_SIZE] << 24;
	i++;
//	dprintf(2, "index + i mod MEM_SIZE = %d\n", index + i % MEM_SIZE);
	ret += g_vm->map[(index + i) % MEM_SIZE] << 16;
	i++;
//	dprintf(2, "index + i mod MEM_SIZE = %d\n", index + i % MEM_SIZE);
	ret += g_vm->map[(index + i) % MEM_SIZE] << 8;
	i++;
//	dprintf(2, "index + i mod MEM_SIZE = %d\n", index + i % MEM_SIZE);
	ret += g_vm->map[(index + i) % MEM_SIZE];
	ft_printf("%x\n", ret);
	return (ret);
}


/*

ADV 5 (0x0000 -> 0x0005) 03 70 01 00 ee
ADV 7 (0x0005 -> 0x000c) 02 90 09 01 1e 00 01
ADV 5 (0x000c -> 0x0011) 03 70 01 ff f4
ADV 7 (0x0011 -> 0x0018) 02 90 00 00 01 fa 02
ADV 7 (0x0800 -> 0x0807) 0b 68 01 00 d2 00 01
ADV 7 (0x0018 -> 0x001f) 02 90 00 00 00 64 03
ADV 5 (0x001f -> 0x0024) 01 00 00 00 00
ADV 7 (0x0807 -> 0x080e) 0b 68 01 00 78 00 01
ADV 7 (0x080e -> 0x0815) 0b 68 01 00 cc 00 01
ADV 7 (0x0815 -> 0x081c) 0b 68 01 00 34 00 01
ADV 7 (0x081c -> 0x0823) 0b 68 01 01 11 00 01
ADV 7 (0x0823 -> 0x082a) 0b 68 01 00 3c 00 01
ADV 7 (0x082a -> 0x0831) 0b 68 01 00 44 00 01
ADV 7 (0x0831 -> 0x0838) 0b 68 01 01 63 00 01
ADV 7 (0x0838 -> 0x083f) 0b 68 01 01 9b 00 01
ADV 7 (0x083f -> 0x0846) 02 90 00 00 00 00 10
ADV 3 (0x0024 -> 0x0027) 0c 00 4b
ADV 7 (0x006f -> 0x0076) 02 90 0b 54 05 01 04
ADV 7 (0x0027 -> 0x002e) 02 90 02 09 01 f5 04
ADV 7 (0x0076 -> 0x007d) 02 90 0b 54 06 01 05
ADV 4 (0x002e -> 0x0032) 03 50 04 05
ADV 7 (0x007d -> 0x0084) 02 90 0b 54 0c 01 06
ADV 7 (0x0032 -> 0x0039) 02 90 03 09 00 5f 06
ADV 7 (0x0084 -> 0x008b) 02 90 0b 54 0d 01 0c
ADV 4 (0x0039 -> 0x003d) 03 50 06 07
ADV 7 (0x008b -> 0x0092) 02 90 0b 54 0e 01 0d
ADV 4 (0x003d -> 0x0041) 03 50 06 0c
ADV 7 (0x0092 -> 0x0099) 02 90 0b 54 0f 01 0e
ADV 4 (0x0041 -> 0x0045) 03 50 06 0d
ADV 7 (0x0099 -> 0x00a0) 02 90 0b 54 07 01 0f
ADV 4 (0x0045 -> 0x0049) 03 50 06 0e
ADV 7 (0x00a0 -> 0x00a7) 02 90 0b 54 08 01 07
ADV 4 (0x0049 -> 0x004d) 03 50 06 0f
ADV 7 (0x00a7 -> 0x00ae) 02 90 0b 54 09 01 08
ADV 4 (0x004d -> 0x0051) 03 50 04 08
ADV 7 (0x00ae -> 0x00b5) 02 90 0b 54 0a 01 09
ADV 4 (0x0051 -> 0x0055) 03 50 04 09
ADV 7 (0x00b5 -> 0x00bc) 02 90 09 01 6a 01 0a
ADV 4 (0x0055 -> 0x0059) 03 50 04 0a
ADV 7 (0x00bc -> 0x00c3) 02 90 09 00 9e 00 0b
ADV 7 (0x0059 -> 0x0060) 02 90 09 fe ac 00 0b
ADV 7 (0x00c3 -> 0x00ca) 02 90 00 00 00 00 01
ADV 7 (0x0060 -> 0x0067) 02 90 00 00 00 04 01
ADV 5 (0x0067 -> 0x006c) 05 54 10 10 10
ADV 6 (0x025d -> 0x0263) 0b 58 04 01 01 f9
ADV 6 (0x025d -> 0x0263) 0b 58 04 01 01 f9
ADV 5 (0x0456 -> 0x045b) 0b 54 05 01 02
ADV 5 (0x0456 -> 0x045b) 0b 54 05 01 02
ADV 3 (0x0846 -> 0x0849) 0c 00 8c
ADV 5 (0x0650 -> 0x0655) 0b 54 06 01 02
ADV 5 (0x08d2 -> 0x08d7) 01 ff ff ff fe
ADV 5 (0x0849 -> 0x084e) 01 0b 54 0c 01
ADV 7 (0x084e -> 0x0855) 02 90 01 df 5e 76 02
ADV 5 (0x0650 -> 0x0655) 0b 54 06 01 02


*/