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

void	convert_short(unsigned char **ptr, int n)
{
	(*ptr)[0] = (n >> 8) & 0xFF;
	(*ptr)[1] = n & 0xFF;
}

void	convert_integer(unsigned char **ptr, int n)
{
	(*ptr)[0] = (n >> 24) & 0xFF;
	(*ptr)[1] = (n >> 16) & 0xFF;
	(*ptr)[2] = (n >> 8) & 0xFF;
	(*ptr)[3] = n & 0xFF;
}

void	write_binary_int(int fd, int nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(4);
	convert_integer(&str, nb);
	write(fd, str, 4);
	free(str);
}

void	write_binary_short(int fd, short nb)
{
	unsigned char	*str;

	str = (unsigned char *)ft_strnew(2);
	convert_short(&str, nb);
	write(fd, str, 2);
	free(str);
}
