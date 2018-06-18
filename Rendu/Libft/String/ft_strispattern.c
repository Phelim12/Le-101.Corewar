/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strispattern.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 21:29:01 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 21:29:01 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strispattern(const char *str, const char *pattern)
{
	int var;

	var = -1;
	while (str[++var])
		if (!(ft_strchr(pattern, str[var])))
			return (0);
	return (1);
}
