/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_asm.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 22:48:37 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 22:48:37 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		cmd_is_good(char *cmd)
{
	if (cmd[0] == CMD_CHAR &&
		ft_strcmp(cmd, CMD_NAME) && ft_strcmp(cmd, CMD_COMMENT))
		return (1);
	if ((ft_count_chars(cmd, NEGATIVE_CHAR)) > 1)
		return (1);
	if (!(ft_strcmp(cmd, "%")))
		return (1);
	if (!(ft_strcmp(cmd, ":")))
		return (1);
	if (!(ft_strcmp(cmd, "-")))
		return (1);
	return (0);
}

int		add_cmd(t_cmd **result, t_pos *pos, char *buf, int fd)
{
	t_cmd	*previous;

	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : (*result);
	(*result) = ft_memalloc(sizeof(t_cmd));
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	(*result)->pos = (*buf == STRING) ? init_pos(pos->y, (pos->x - 1)) : *pos;
	(*buf) = take_elem(pos, &((*result)->data), (*buf), fd);
	if ((*buf) != STRING_CHAR && cmd_is_good((*result)->data))
		return (0);
	(*result)->token = token_dispenser((*result)->data, (*buf));
	return (1);
}

int		add_line(t_line **result, t_pos *pos, char *buf, int fd)
{
	t_line	*previous;
	int		ret;

	ret = add_cmd(&((*result)->line), pos, buf, fd);
	(*pos) = init_pos((pos->y + 1), 1);
	if (!((*result)->line))
		return (ret);
	else
		(*result)->line = (*result)->line->start;
	previous = (*result);
	(*result) = (*result)->next;
	(*result) = ft_memalloc(sizeof(t_line));
	(*result)->prev = previous;
	previous->next = (*result);
	(*result)->start = previous->start;
	return (ret);
}

t_line	*parser(t_line *result, int fd)
{
	t_pos		pos;
	char		buf;
	int			ret;

	init_reader(&result, &pos, &buf, &ret);
	while ((ret = special_read(&pos, &buf, ret, fd)))
	{
		if ((!(ft_strchr(VALID_CHARS, buf)) && !(ft_iscntrl(buf))))
			print_error_lexical(result, pos);
		else if (buf == COMMENT_CHAR)
			ret = pass_comment(&buf, fd);
		else if ((buf == LINE_CHAR) || !(result))
			ret = add_line(&result, &pos, &buf, fd);
		else if (ft_strchr(VALID_CHARS, buf))
			if (!(add_cmd(&(result->line), &pos, &buf, fd)))
				print_error_lexical(result, result->line->pos);
	}
	add_cmd(&(result->line), &pos, (char *)&ret, fd);
	return ((result) ? result->start : NULL);
}
