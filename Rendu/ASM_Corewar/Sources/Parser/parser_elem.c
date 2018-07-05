/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_elem.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 23:30:09 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 23:30:09 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		stop_elem(char *str, char start, char buf, int var)
{
	if (start == CHAR_STRING)
		return ((buf == CHAR_STRING) ? 1 : 0);
	if (buf == CHAR_LABEL && ft_strchr(str, CHAR_LABEL))
		return (1);
	if (buf == CHAR_DIRECT && ft_strchr(str, CHAR_DIRECT))
		return (1);
	if (var && str[0] != CHAR_DIRECT && str[var] == CHAR_LABEL)
		return (1);
	return (0);
}

char	*init_parser_elem(char **str, int *var, char start, char buf)
{
	(*str) = ft_strnew(BUFF_ELEM);
	(*var) = (start == CHAR_STRING) ? -1 : 0;
	(*str)[0] = (start != CHAR_STRING) ? start : 0;
	if (start == CHAR_NEGATIVE)
		return (CHARS_NUMBER);
	if (start == CHAR_CMD)
		return (CHARS_CMD);
	if (start == CHAR_DIRECT && buf == CHAR_LABEL)
		return (CHARS_LABEL);
	if (start == CHAR_DIRECT)
		return (CHARS_DIRECT);
	if (ft_strchr(CHARS_LABEL, start))
		return (CHARS_LABEL);
	return (NULL);
}

char	parser_elem(t_pos *pos, char **str, char start, int fd)
{
	char	*pattern;
	char	buf;
	int		ret;
	int		var;

	ret = read(fd, &buf, 1);
	pattern = init_parser_elem(str, &var, start, buf);
	while (ret > 0)
	{
		*pos = (buf == CHAR_LINE && start == CHAR_STRING) \
		? init_pos(pos->y + 1, 0) : init_pos(pos->y, pos->x + 1);
		if (stop_elem(*str, start, buf, var))
			return (buf);
		if (start != CHAR_STRING && (!pattern || !(ft_strchr(pattern, buf))))
			return (buf);
		if ((var > 0) && !(var % (BUFF_ELEM - 1)))
			(*str) = realloc_str((*str), var);
		(*str)[++var] = buf;
		ret = read(fd, &buf, 1);
	}
	return (0);
}
