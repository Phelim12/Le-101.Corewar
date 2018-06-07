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

char	*chars_stop_elem(int *ptr, char start)
{
	if (start == QUOTE)
		(*ptr) = -1;
	if (start == QUOTE)
		return (STR_1);
	if (start == SHARP)
		return (STR_2);
	if (start == POINT)
		return (STR_3);
	if (ft_strchr(LABEL_CHARS, start))
		return (STR_4);
	return (NULL);
}

char	take_elem(char **str, char start, int fd)
{
	char	*stop;
	char	chr;
	int		var;

	var = 0;
	(*str) = ft_strnew(BUFF_ELEM);
	stop = chars_stop_elem(&var, start);
	if (start != QUOTE)
		(*str)[var] = start;
	while (read(fd, &chr, 1) > 0)
	{
		if ((!(stop)) || (ft_strchr(stop, chr)))
			return (chr);
		if (((var % (BUFF_ELEM - 1)) == 0) && (var > 0))
			(*str) = realloc_str((*str), var);
		(*str)[++var] = chr;
	}
	return (-1);
}

t_cmd	*reader(int index, int fd)
{
	t_cmd		*previous;
	t_cmd		*pointer;
	char		chr;
	int			ret;

	pointer = NULL;
	previous = NULL;
	ret = read(fd, &chr, 1);
	while (ret && chr != -1)
	{
		if (!(ft_strchr(SPACE_CHARS, chr)))
		{
			previous = (pointer) ? pointer : NULL;
			pointer = (pointer) ? pointer->next : pointer;
			pointer = ft_memalloc(sizeof(t_cmd));
			if ((pointer->prev = (previous) ? previous : NULL))
				previous->next = pointer;
			pointer->start = (previous) ? previous->start : pointer;
			chr = take_elem(&(pointer->data), chr, fd);
			pointer->index = index++;
			printf("[%s] ", pointer->data); // No 26 lines in NORMINETTE
		}
		if (ft_strchr(SPACE_CHARS, chr) || chr == 34)
			ret = read(fd, &chr, 1);
	}
	return (pointer->start);
}
