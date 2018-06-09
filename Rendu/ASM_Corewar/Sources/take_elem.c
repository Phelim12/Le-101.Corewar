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

#include "../Includes/main_asm.h"

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

char	*init_params_take_elem(char **str, int *var, char start)
{
	(*str) = ft_strnew(BUFF_ELEM);
	(*var) = (start == QUOTE) ? -1 : 0;
	(*str)[0] = (start != QUOTE) ? start : 0;
	if (start == DASH)
		return (NUMBER_CHARS);
	if (start == POINT)
		return (HEADER_CHARS);
	if (ft_strchr(LABEL_CHARS, start))
		return (LABEL_CHARS);
	return (NULL);
}

void	refresh_pos_token(t_pos *position, char start, char buf, int option)
{
	if (!(option))
	{
		if (start == NEW_LINE)
		{
			position->x = 0;
			position->y += 1;
		}
	}
	else
	{
		if (buf == NEW_LINE && start == QUOTE)
		{
			position->x = 0;
			position->y += 1;
		}
		if (buf != NEW_LINE)
			position->x += 1;
	}
}

char	take_elem(t_pos *position, char **str, char start, int fd)
{
	char	*pattern;
	char	buf;
	int		ret;
	int		var;

	refresh_pos_token(position, start, buf, 0);
	pattern = init_params_take_elem(str, &var, start);
	while ((ret = read(fd, &buf, 1)) > 0)
	{
		refresh_pos_token(position, start, buf, 1);
		if ((start == QUOTE && buf == QUOTE) ||
			(start == SHARP && buf == NEW_LINE))
			return (buf);
		if ((start != QUOTE && start != SHARP) &&
			(!(pattern) || !(ft_strchr(pattern, buf))))
			return (buf);
		if ((var > 0) && !(var % (BUFF_ELEM - 1)))
			(*str) = realloc_str((*str), var);
		(*str)[++var] = buf;
	}
	return (-1);
}
