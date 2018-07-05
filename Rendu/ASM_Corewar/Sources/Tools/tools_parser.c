/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_parser.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 17:48:13 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 17:48:13 by clcreuso    ###    #+. /#+    ###.fr     */
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

void	init_parser(t_line **ptr, t_pos *pos, char *buf, int *ret)
{
	(*buf) = 0;
	(*ret) = 1;
	(*pos) = init_pos(1, 0);
	(*ptr) = ft_memalloc(sizeof(t_line));
	(*ptr)->start = (*ptr);
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

int		pass_comment(t_cmd *cmds, char *buf, int fd)
{
	while ((read(fd, buf, 1)) > 0)
		if ((*buf) == CHAR_LINE)
		{
			if (cmds && !(cmds->data))
				read(fd, buf, 1);
			return (1);
		}
	return (0);
}

int		special_read(t_pos *pos, char *buf, int ret, int fd)
{
	if (!(ret))
		return (0);
	if (ft_iscntrl(*buf) && (*buf) != 10)
	{
		if ((ret = read(fd, buf, 1)) < 0)
			return (0);
		if (*buf)
			pos->x++;
		return ((*buf) ? ret : 0);
	}
	return (1);
}
