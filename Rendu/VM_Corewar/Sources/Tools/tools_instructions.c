/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_instructions.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:47:49 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 15:59:44 by nbettach    ###    #+. /#+    ###.fr     */
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

unsigned int		read_map(int index, int size)
{
	int					i;
	unsigned int		ret;

	i = 0;
	ret = 0;
	index %= MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
	ret += g_vm->map[index + i++] << 24;
	ret += g_vm->map[index + i++] << 16;
	ret += g_vm->map[index + i++] << 8;
	ret += g_vm->map[index + i++];
	return (ret);
}
