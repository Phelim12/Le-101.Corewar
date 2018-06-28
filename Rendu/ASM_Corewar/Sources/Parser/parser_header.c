/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_header.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 23:27:18 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 23:27:18 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int			token_header(int token)
{
	if (token == END)
		return (1);
	if (token == ENDLINE)
		return (1);
	if (token == COMMAND_NAME)
		return (1);
	if (token == COMMAND_COMMENT)
		return (1);
	return (0);
}

t_line		*delete_header(t_line *file, int size_header)
{
	t_line	*result;
	int		line;

	line = 0;
	while ((file = file->next))
		if (++line < size_header)
		{
			file->start = file;
			free_line(file->prev->line);
			ft_memdel((void **)&(file->prev));
		}
		else if ((result = file->prev->start))
			file->start = result;
	return (result);
}

void		parser_name(char *result, t_line *file)
{
	t_cmd	*line;

	line = file->line->next;
	if (line->token != STRING)
		print_error_token(file, line, SYNTAX_MSG);
	if (line->next->token != ENDLINE)
		print_error_token(file, line->next, SYNTAX_MSG);
	if (ft_strlen(line->data) <= NAME_LENGTH)
		ft_strncpy(result, line->data, NAME_LENGTH);
	else
		print_error_size_header(file, "name", NAME_LENGTH);
}

void		parser_comment(char *result, t_line *file)
{
	t_cmd	*line;

	line = file->line->next;
	if (line->token != STRING)
		print_error_token(file, line, SYNTAX_MSG);
	if (line->next->token != ENDLINE)
		print_error_token(file, line->next, SYNTAX_MSG);
	if (ft_strlen(line->data) <= COMMENT_LENGTH)
		ft_strncpy(result, line->data, COMMENT_LENGTH);
	else
		print_error_size_header(file, "comment", COMMENT_LENGTH);
}

t_header	parser_header(t_line **file, int comment, int name)
{
	t_header	result;
	int			line;

	line = 0;
	result.prog_size = (*file)->size;
	result.magic = COREWAR_EXEC_MAGIC;
	while (++line && token_header((*file)->line->token))
	{
		if ((*file)->line->token == COMMAND_NAME && name--)
			parser_name(result.name, (*file));
		else if ((*file)->line->token == COMMAND_COMMENT && comment--)
			parser_comment(result.comment, (*file));
		else if ((*file)->line->token != ENDLINE)
			print_error_token((*file), (*file)->line, SYNTAX_MSG);
		(*file) = (*file)->next;
	}
	if (name || comment)
		print_error_token((*file), (*file)->line, SYNTAX_MSG);
	(*file) = delete_header((*file)->start, line);
	return (result);
}
