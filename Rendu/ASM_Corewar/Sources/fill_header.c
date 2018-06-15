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

char	*fill_prog_name(t_line *file, t_cmd *line)
{
	char result[PROG_NAME_LENGTH + 1];

	if (line->token)
		print_error_token(file, line, line->data);
	if (!(line->next))
		print_error_token(file, line, "ENDLINE");
	line = line->next;
	if (line->next)
		print_error_token(file, line->next, line->next->data);
	if (!(line->token))
		print_error_token(file, line, line->data);
	if (ft_strlen(line->data) < PROG_NAME_LENGTH)
		return (line->data);
	else
		print_error_size_header(file, "name", PROG_NAME_LENGTH);
	return (NULL);
}

char	*fill_comment(t_line *file, t_cmd *line)
{
	char result[COMMENT_LENGTH + 1];

	if (line->token)
		print_error_token(file, line, line->data);
	if (!(line->next))
		print_error_token(file, line, "ENDLINE");
	line = line->next;
	if (line->next)
		print_error_token(file, line->next, line->next->data);
	if (!(line->token))
		print_error_token(file, line, line->data);
	if (ft_strlen(line->data) < COMMENT_LENGTH)
		return (line->data);
	else
		print_error_size_header(file, "comment", COMMENT_LENGTH);
	return (NULL);
}

t_header	fill_header(t_line *file)
{
	t_header	result;
	int			count;

	count = 0;
	while (count++ < 2)
	{
		if (!(ft_strcmp(file->line->data, NAME_CMD_STRING)))
			ft_strncpy(result.prog_name, fill_prog_name(file, file->line), PROG_NAME_LENGTH);
		else if (!(ft_strcmp(file->line->data, COMMENT_CMD_STRING)))
			ft_strncpy(result.comment, fill_comment(file, file->line), COMMENT_LENGTH);
		else
			print_error_token(file, file->line, file->line->data);
		file = file->next;
	}
	return (result);
}
