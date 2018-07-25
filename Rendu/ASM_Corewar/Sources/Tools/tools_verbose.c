/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:16:24 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 16:16:24 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	verbose_binary_int(int nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	verbose_convert_integer(&str, nb);
	free(str);
}

void	verbose_binary_short(short nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(2);
	verbose_convert_short(&str, nb);
	free(str);
}

void	verbose_register(t_cmd *ptr)
{
	char	*ptr1;

	ft_printf("\n\t\t\t\t%s->%s %-20s -> [%s%s - %s0b01%s - 0x%02s]",
			RED, C_END,
			ptr->data, ITLC, token_name(ptr->token),
			GREEN, C_END,
			ptr1 = ft_utoa_base((char)ft_atoi(ptr->data + 1),
				"0123456789abcdef"));
	ft_memdel((void**)&ptr1);
}

void	verbose_convert_short(unsigned char **ptr, int n)
{
	char *ptr1;
	char *ptr2;

	(*ptr)[0] = (n >> 8) & 0xFF;
	(*ptr)[1] = n & 0xFF;
	ft_printf(" 0x%02s  0x%02s]",
		ptr1 = ft_utoa_base((*ptr)[0], "0123456789abcdef"),
		ptr2 = ft_utoa_base((*ptr)[1], "0123456789abcdef"));
	ft_memdel((void**)&ptr1);
	ft_memdel((void**)&ptr2);
}

void	verbose_convert_integer(unsigned char **ptr, int n)
{
	char *ptr1;
	char *ptr2;
	char *ptr3;
	char *ptr4;

	(*ptr)[0] = (n >> 24) & 0xFF;
	(*ptr)[1] = (n >> 16) & 0xFF;
	(*ptr)[2] = (n >> 8) & 0xFF;
	(*ptr)[3] = n & 0xFF;
	ft_printf(" 0x%02s  0x%02s  0x%02s  0x%02s]",
		ptr1 = ft_utoa_base((*ptr)[0], "0123456789abcdef"),
		ptr2 = ft_utoa_base((*ptr)[1], "0123456789abcdef"),
		ptr3 = ft_utoa_base((*ptr)[2], "0123456789abcdef"),
		ptr4 = ft_utoa_base((*ptr)[3], "0123456789abcdef"));
	ft_memdel((void**)&ptr1);
	ft_memdel((void**)&ptr2);
	ft_memdel((void**)&ptr3);
	ft_memdel((void**)&ptr4);
}
