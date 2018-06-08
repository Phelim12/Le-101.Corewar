/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 18:52:58 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 20:35:08 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"

t_pos	init_pos(int y, int x)
{
	t_pos	result;

	result.x = x;
	result.y = y;
	return (result);
}

char	*init_params_take_elem(char **str, int *var, char start)
{
	(*str) = ft_strnew(BUFF_ELEM);
	(*var) = (start == QUOTE) ? -1 : 0;
	(*str)[0] = (start != QUOTE) ? start : 0;
	if (start == POINT)
		return (HEADER_CHARS);
	if (ft_strchr(LABEL_CHARS, start))
		return (LABEL_CHARS);
	return (NULL);
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

void	refresh_pos_token(t_pos *pos, char start, char buffer, int option)
{
	if (!(option))
	{
		if (start == NEW_LINE)
		{
			pos->x = 0;
			pos->y += 1;
		}
	}
	else
	{
		if (buffer == NEW_LINE && start == QUOTE)
		{
			pos->x = 0;
			pos->y += 1;
		}
		if (buffer != NEW_LINE)
			pos->x += 1;
	}
}

char	take_elem(t_pos *pos, char **str, char start, int fd)
{
	char	*pattern;
	char	buffer;
	int		ret;
	int		var;

	refresh_pos_token(pos, start, buffer, 0);
	pattern = init_params_take_elem(str, &var, start);
	while ((ret = read(fd, &buffer, 1)) > 0)
	{
		refresh_pos_token(pos, start, buffer, 1);
		if ((start == QUOTE && buffer == QUOTE) ||
			(start == SHARP && buffer == NEW_LINE))
			return (buffer);
		if ((start != QUOTE && start != SHARP) &&
			(!(pattern) || !(ft_strchr(pattern, buffer))))
			return (buffer);
		if ((var > 0) && !(var % (BUFF_ELEM - 1)))
			(*str) = realloc_str((*str), var);
		(*str)[++var] = buffer;
	}
	return (-1);
}

int		find_buffer_elem(t_pos *pos, char *buffer, int fd)
{
	if (pos->x == 1 && pos->y == 1)
		return (read(fd, buffer, 1));
	if (ft_strchr(SPACE_CHARS, *buffer) || *buffer == 34)
		pos->x++;
	if (ft_strchr(SPACE_CHARS, *buffer) || *buffer == 34)
		return (read(fd, buffer, 1));
	else
		return (1);
}

t_cmd	*reader(int fd)
{
	t_cmd		*previous;
	t_cmd		*pointer;
	t_pos		pos;
	char		buffer;
	int			ret;

	pointer = NULL;
	previous = NULL;
	pos = init_pos(1, 1);
	while ((ret = find_buffer_elem(&pos, &buffer, fd)) && buffer != -1)
	{	
		if (!(ft_strchr(SPACE_CHARS, buffer)))
		{
			previous = (pointer) ? pointer : NULL;
			pointer = (pointer) ? pointer->next : pointer;
			pointer = ft_memalloc(sizeof(t_cmd));
			if ((pointer->prev = (previous) ? previous : NULL))
				previous->next = pointer;
			pointer->start = (previous) ? previous->start : pointer;
			pointer->pos = pos;
			buffer = take_elem(&(pos), &(pointer->data), buffer, fd);
			ft_printf("<%c>[%s] ", buffer, pointer->data); // No 26 lines in NORMINETTE
		}
	}
	return (pointer->start);
}
