/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 14:32:52 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 11:19:04 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		add_label(t_label **result, t_cmd **line)
{
	t_label	*previous;

	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : *result;
	if (!((*result) = ft_memalloc(sizeof(t_label))))
		return (1);
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
	(*result)->name = ft_strdup((*line)->data);
	(*result)->name[ft_strlen((*result)->name + 1)] = 0;
	return (0);
}


int		init_label_next(t_line *tmpfile, t_label **result)
{
	while (tmpfile)
	{
		if ((tmpfile->line->token == INSTRUCTION) ||
				(tmpfile->line->token == END))
		{
			(*result)->go_to = tmpfile->line;
			return (0);
		}
		else if (tmpfile->line->token == LABEL || tmpfile->line->token == ENDLINE)
		{
			tmpfile = tmpfile->next;
			continue ;
		}
		else
		{
			printf("Error1: [%s] TOKEN: %s\n", tmpfile->line->data, token_name(tmpfile->line->token));
			(*result)->go_to = tmpfile->line;
			return (1);
		}
		tmpfile = tmpfile->next;
	}
	return (0);
}

int		init_label(t_label **result, t_line **file, t_cmd **line)
{
	if (((*line)->next->token != INSTRUCTION) && ((*line)->next->token != ENDLINE))
		return (1);
	else if ((*line)->next->token == INSTRUCTION)
		(*result)->go_to = (*line)->next;
	else
	{
		if ((init_label_next((*file)->next, &(*result))))
			return (1);
	}
	return (0);
}
