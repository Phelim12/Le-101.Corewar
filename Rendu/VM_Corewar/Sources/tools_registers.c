/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_registers.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 15:56:19 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 17:41:42 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static long long int	fill_the_bone(long long int val)
{
	long long int	n;

	n = 0xff;
	while ((n & val) != val)
		n = (n << 8) | 0xff;
	n = ~n;
	val = n | val;
	return (val);
}

/*
** Extract from a tab the index-ieme value  when the tab is cut by v_size bytes
** MSB is the most significant byte
*/

long long int	extract(unsigned char *tab, unsigned char v_size,
		unsigned char index, int t_size)
{
	int				i;
	int				b;
	long long int	val;
	long long int	msb;

	i = 0;
	while (i < t_size && i < index * v_size)
		i += v_size;
	b = i;
	val = tab[i];
	msb = 0x80;
	while (b < i + v_size - 1)
	{
		val = (val << 8) | tab[b + 1];
		msb = (msb << 8);
		b++;
	}
	if ((msb & val) == msb)
	{
		val = fill_the_bone(val);
		ft_printf("msb : %lld and val : %lld\n", msb, val);
	}
	return (val);
}
