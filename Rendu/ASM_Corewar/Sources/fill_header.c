/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_header.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 17:08:56 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:08:58 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void		fill_name(char *result, t_line *file, t_cmd *line)
{
	if (line->token == STRING)
		print_error_token(file, line->pos, line->data, line->token);
	if (!(line->next))
		print_error_token(file, line->pos, line->data, ENDLINE);
	line = line->next;
	if (line->next)
	{
		line = line->next;
		print_error_token(file, line->pos, line->data, line->token);
	}
	if (line->token != STRING)
		print_error_token(file, line->pos, line->data, line->token);
	if (ft_strlen(line->data) < NAME_LENGTH)
		ft_strncpy(result, line->data, NAME_LENGTH);
	else
		print_error_size_header(file, "name", NAME_LENGTH);
}

void		fill_comment(char *result, t_line *file, t_cmd *line)
{
	if (line->token == STRING)
		print_error_token(file, line->pos, line->data, line->token);
	if (!(line->next))
		print_error_token(file, line->pos, line->data, ENDLINE);
	line = line->next;
	if (line->next)
	{
		line = line->next;
		print_error_token(file, line->pos, line->data, line->token);
	}
	if (line->token != STRING)
		print_error_token(file, line->pos, line->data, line->token);
	if (ft_strlen(line->data) < COMMENT_LENGTH)
		ft_strncpy(result, line->data, COMMENT_LENGTH);
	else
		print_error_size_header(file, "comment", COMMENT_LENGTH);
}

/*t_line		*delete_header(t_line *file)
{
	t_line	*line;
	int		var;

	var = 0;
	while (file->next)
	{
		file = file->next;
		if (var++ < 2)
		{
			file->start = file;
			line = file->prev;
			free_line(line->line);
			ft_memdel((void **)&line);
			file->prev = NULL;
		}
		else
			file->start = file->prev->start;
	}
	file->start = file->prev->start;
	return (file->start);
}*/

t_header	fill_header(t_line **file, int comment, int name)
{
	t_header	result;
	t_cmd		*line;

	while (comment || name)
	{
		line = (*file)->line;
		if (!(ft_strcmp(line->data, CMD_NAME)) && name--)
			fill_name(result.name, (*file), line);
		else if (!(ft_strcmp(line->data, CMD_COMMENT)) && comment--)
			fill_comment(result.comment, (*file), line);
		else
			print_error_token((*file), line->pos, line->data, line->token);
		(*file) = (*file)->next;
	}
	// (*file) = delete_header((*file)->start);
	return (result);
}
