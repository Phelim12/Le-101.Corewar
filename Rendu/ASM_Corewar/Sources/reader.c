/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 18:52:58 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 18:25:08 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"

int		token_dispenser(char *cmd, char buf)
{
	int	end;

	end = ft_strlen(cmd + 1);
	if (buf == STRING_CHAR)
		return (STRING);
	if (cmd[0] == DIRECT_CHAR && cmd[1] == LABEL_CHAR)
		return (DIRECT_LABEL);
	if (cmd[end] == LABEL_CHAR)
		return (LABEL);
	if ((*cmd) == DIRECT_CHAR)
		return (DIRECT);
	if ((*cmd) == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if ((*cmd) == SEPARATOR_CHAR && !(cmd[1]))
		return (SEPARATOR);
	if (ft_strstrchr(cmd, DIRECT_CHARS))
		return (INDIRECT);
	if (!(ft_strcmp(cmd, CMD_NAME)))
		return (COMMAND_NAME);
	if (ft_strstrchr(cmd, INSTRUCTION_CHARS))
		return (INSTRUCTION);
	if (!(ft_strcmp(cmd, CMD_COMMENT)))
		return (COMMAND_COMMENT);
	return (0);
}

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

int		add_cmd(t_cmd **result, t_pos *position, char *buf, int fd)
{
	t_cmd	*previous;

	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : *result;
	(*result) = ft_memalloc(sizeof(t_cmd));
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	(*result)->pos = (*position);
	(*buf) = take_elem(position, &((*result)->data), (*buf), fd);
	ft_printf("%15s -> ", (*result)->data);
	if ((*buf) != STRING_CHAR && error_on_cmd((*result)->data, (*buf)))
		return (0);
	(*result)->token = token_dispenser((*result)->data, (*buf));
	ft_printf("%s\n", token_name((*result)->token));
	return (1);
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
		if (errno || (!(ft_strchr(VALID_CHARS, buf)) && (buf < 0 || buf > 32)))
			print_error_reader(result, position);
		else if (buf == COMMENT_CHAR)
			ret = skip_comment(&position, &buf, fd);
		else if ((buf == LINE_CHAR) || !(result))
			ret = add_line(&result, &position, &buf, fd);
		else if (ft_strchr(VALID_CHARS, buf))
			if (!(add_cmd(&(result->line), &position, &buf, fd)))
				print_error_reader(result, result->line->pos);
	}
	return ((result) ? result->start : NULL);
}
