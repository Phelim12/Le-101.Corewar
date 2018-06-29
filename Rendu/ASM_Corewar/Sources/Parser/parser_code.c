/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser_code.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:18:12 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 16:18:12 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void		parser_code(t_line *file)
{
	t_line	*tmp;
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line;
		while (ptr)
		{
			if ((ptr->token == END && ptr->prev) ||
				(ptr->token == COMMAND_NAME || ptr->token == COMMAND_COMMENT))
				print_error_token(file, ptr, SYNTAX_MSG);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}