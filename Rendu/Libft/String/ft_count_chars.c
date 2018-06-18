/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_chars.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 21:31:03 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 21:31:03 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_chars(const char *str, char chr)
{
	int result;
	int var;

	var = -1;
	result = 0;
	while (str[++var])
		if (str[var] == chr)
			result++;
	return (result);
}
