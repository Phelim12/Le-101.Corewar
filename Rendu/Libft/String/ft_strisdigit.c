/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strisdigit.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 21:21:15 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 21:21:15 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisdigit(const char *str)
{
	int cur;

	cur = 0;
	if (!(ft_strchr("+-", str[cur])) && !(ft_isdigit(str[cur])))
		return (0);
	if (ft_strchr("+-", str[cur]) && !(ft_isdigit(str[cur + 1])))
		return (0);
	while (str[++cur])
		if (!(ft_isdigit(str[cur])))
			return (0);
	return (1);
}
