/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_label.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 17:13:21 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/23 17:13:21 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

t_label	*init_parser_label(void)
{
	t_label	*result;

	result = ft_memalloc(sizeof(t_label));
	result->start = result;
	result->prev = NULL;
	return (result);
}

t_cmd	*init_label_value(t_line *file, t_cmd *line)
{
	t_cmd	*ptr;

	if (line->next->token == INSTRUCTION)
		return (line->next);
	if (line->next->token != ENDLINE)
		print_error_token(file, line->next, SYNTAX_MSG);
	while ((file = file->next))
	{
		ptr = file->line->start;
		if ((ptr->token == INSTRUCTION) || (ptr->token == END))
			return (ptr);
		if (ptr->token != LABEL && ptr->token != ENDLINE)
			print_error_token(file, ptr, SYNTAX_MSG);
	}
	return (NULL);
}

void	add_label(t_label **result, t_line *file, t_cmd *line)
{
	t_label	*previous;

	if ((*result)->name)
	{
		previous = (*result);
		(*result) = (*result)->next;
		(*result) = ft_memalloc(sizeof(t_label));
		(*result)->prev = previous;
		previous->next = (*result);
		(*result)->start = previous->start;
	}
	(*result)->adress = line;
	(*result)->name = ft_strdup(line->data);
	(*result)->name[ft_strlen((*result)->name + 1)] = 0;
	(*result)->value = init_label_value(file, line);
}

void	parser_label(t_line *file)
{
	t_label *label;
	t_line	*tmp;

	tmp = file;
	label = init_parser_label();
	while (tmp)
	{
		if (tmp->line->start->token == LABEL)
			add_label(&label, tmp, tmp->line->start);
		tmp->label = label->start;
		tmp = tmp->next;
	}
	check_duplicate_label(label->start, file);
	label_exist(file->start, label->start);
}
