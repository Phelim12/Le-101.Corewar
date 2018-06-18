/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 23:30:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 23:30:38 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		pass_comment(char *buf, int fd)
{
	while ((read(fd, buf, 1)) > 0)
		if ((*buf) == LINE_CHAR)
			return (1);
	return (0);
}

int		special_read(t_pos *pos, char *buf, int ret, int fd)
{
	if (!(ret))
		return (0);
	if ((ft_iscntrl(*buf) && (*buf) != 10) || (*buf) == 34)
		return (((read(fd, buf, 1)) > 0) ? pos->x++ : 0);
	return (1);
}

void	init_parser(t_line **result, t_pos *pos, char *buf, int *ret)
{
	(*buf) = 0;
	(*ret) = 1;
	(*pos) = init_pos(1, 1);
	(*result) = ft_memalloc(sizeof(t_line));
	(*result)->start = (*result);
}
