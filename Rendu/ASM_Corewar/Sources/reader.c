/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 18:52:58 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 14:57:55 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"
#include <errno.h>  

int		find_buffer_elem(t_pos *position, char *buf, int ret, int fd)
{
	if (!(ret))
		return (0);
	if ((*buf) == 10 || (*buf) == 33)
		return (1);
	if ((*buf) > 0 && (*buf) < 35)
		position->x++;
	if ((*buf) >= 0 && (*buf) < 35)
		return (read(fd, buf, 1));
	return (1);
}

void	print_error_reader(t_line *result, t_pos position)
{
	if (result)
		result = result->start;
	free_file(result);
	if (errno)
		perror("Error fd");
	else
	{
		ft_putstr_fd("Lexical error at [", 2);
		ft_putnbr_fd(position.y, 2);
		ft_putchar_fd(':', 2);
		ft_putnbr_fd(position.x, 2);
		ft_putendl_fd("]", 2);
	}
	exit(EXIT_FAILURE);
}

void	add_cmd(t_cmd **result, t_pos *position, char *buf, int fd)
{
	t_cmd	*previous;

	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : *result;
	(*result) = ft_memalloc(sizeof(t_cmd));
	(*result)->pos = (*position);
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	(*buf) = take_elem(position, &((*result)->data), (*buf), fd);
}

int		add_line(t_line **result, t_pos *position, char *buf, int fd)
{
	t_line	*previous;
	int		ret;

	ret = 1;
	if ((*result))
	{
		ret = read(fd, buf, 1);
		(*position) = init_pos((position->y + 1), 1);
		if (!((*result)->line))
			return (ret);
		else
			(*result)->line = (*result)->line->start;
	}
	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : *result;
	(*result) = ft_memalloc(sizeof(t_line));
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	return (ret);
}

t_line	*reader(t_line *result, t_line *previous, int fd)
{
	t_pos		position;
	char		buf;
	int			ret;

	buf = 0;
	ret = 1; 
	position = init_pos(1, 1);
	while (buf != -1 && (ret = find_buffer_elem(&position, &buf, ret, fd)))
	{
		if (errno || (!(ft_strchr(VALID_CHARS, buf)) && 
			(buf < 0 || buf > 34 || buf == 33)))
			print_error_reader(result, position);
		else if ((buf == NEW_LINE) || !(result))
			ret = add_line(&result, &position, &buf, fd);
		else if (ft_strchr(VALID_CHARS, buf))
			add_cmd(&(result->line), &position, &buf, fd);
	}
	return ((result) ? result->start : NULL);
}
