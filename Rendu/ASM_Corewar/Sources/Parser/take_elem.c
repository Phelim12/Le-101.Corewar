/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   take_elem.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:51:41 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:51:41 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		stop_elem(char *str, char start, char buf, int var)
{
	if (start == STRING_CHAR)
		return ((buf == STRING_CHAR) ? 1 : 0);
	if (buf == LABEL_CHAR && ft_strchr(str, LABEL_CHAR))
		return (1);
	if (buf == DIRECT_CHAR && ft_strchr(str, DIRECT_CHAR))
		return (1);
	if (var && str[0] != DIRECT_CHAR && str[var] == LABEL_CHAR)
		return (1);
	return (0);
}

char	*init_take_elem(char **str, int *var, char start, char buf)
{
	(*str) = ft_strnew(BUFF_ELEM);
	(*var) = (start == STRING_CHAR) ? -1 : 0;
	(*str)[0] = (start != STRING_CHAR) ? start : 0;
	if (start == NEGATIVE_CHAR)
		return (NUMBER_CHARS);
	if (start == CMD_CHAR)
		return (CMD_CHARS);
	if (start == DIRECT_CHAR && buf == LABEL_CHAR)
		return (LABEL_CHARS);
	if (start == DIRECT_CHAR)
		return (DIRECT_CHARS);
	if (ft_strchr(LABEL_CHARS, start))
		return (LABEL_CHARS);
	return (NULL);
}

char	take_elem(t_pos *pos, char **str, char start, int fd)
{
	char	*pattern;
	char	buf;
	int		ret;
	int		var;

	ret = read(fd, &buf, 1);
	pattern = init_take_elem(str, &var, start, buf);
	while (ret > 0)
	{
		*pos = (buf == LINE_CHAR && start == STRING_CHAR) \
		? init_pos(pos->y + 1, 0) : init_pos(pos->y, pos->x + 1);
		if (stop_elem(*str, start, buf, var))
			return (buf);
		if (start != STRING_CHAR && (!pattern || !(ft_strchr(pattern, buf))))
			return (buf);
		if ((var > 0) && !(var % (BUFF_ELEM - 1)))
			(*str) = realloc_str((*str), var);
		(*str)[++var] = buf;
		ret = read(fd, &buf, 1);
	}
	return (0);
}
