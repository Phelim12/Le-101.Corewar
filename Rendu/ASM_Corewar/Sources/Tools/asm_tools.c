/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_asm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:53:36 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 15:16:51 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

t_pos	init_pos(int y, int x)
{
	t_pos	result;

	result.x = x;
	result.y = y;
	return (result);
}

char	*realloc_str(char *str, int size)
{
	char	*result;
	int		var;

	var = -1;
	result = ft_strnew(size + BUFF_ELEM);
	while (str && str[++var])
		result[var] = str[var];
	free(str);
	return (result);
}
