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
#include <errno.h>  

void	print_error_errno(t_cmd *result)
{
	if (result)
		result = result->start;
	free_list(result);
	perror("Error fd");
	exit(EXIT_FAILURE);
}

int		find_buffer_elem(t_pos *position, char *buf, int fd)
{
	if ((*buf) == 10 || (*buf) == 33)
		return (1);
	if ((*buf) >= 0 && (*buf) < 35)
		position->x++;
	if ((*buf) >= 0 && (*buf) < 35)
		return (read(fd, buf, 1));
	return (1);
}

void	add_elem(t_cmd **result, t_pos *position, char *buf, int fd)
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
	ft_printf("[%s] ", (*result)->data);
}

void	print_error_reader(t_cmd *result, t_pos position)
{
	if (result)
		result = result->start;
	free_list(result);
	ft_putstr_fd("Lexical error at [", 2);
	ft_putnbr_fd(position.y, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(position.x, 2);
	ft_putendl_fd("]", 2);
	exit(EXIT_FAILURE);
}

t_cmd	*reader(t_cmd *result, t_cmd *previous, int fd)
{
	t_pos		position;
	char		buf;
	int			ret;

	buf = 0;
	position = init_pos(1, 0);
	while (buf != -1 && (ret = find_buffer_elem(&position, &buf, fd)))
	{
		if (ft_strchr(VALID_CHARS, buf))
			add_elem(&result, &position, &buf, fd);
		else if (buf < 0 || buf > 34 || buf == 33)
			print_error_reader(result, position);
		else if (errno)
			print_error_errno(result);
	}
	if (result)
		return (result->start);
	return (NULL);
}
