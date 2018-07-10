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

int		stop_params(t_line *file, t_cmd *result, t_op info)
{
	static int	cur = 0;

	if (info.params[++cur])
	{
		if (result->token != SEPARATOR)
			print_error_token(file, result, SYNTAX_MSG);
		return (0);
	}
	else
	{
		if (result->token != ENDLINE)
			print_error_token(file, result, SYNTAX_MSG);
		else
			cur = 0;
	}
	return (1);
}

int		parser_params(t_line *file, t_cmd *cmds, int *info_params)
{
	t_op	info;
	int		type;
	int		result;

	info = instruction_exist(cmds->data);
	result = (info.info_params) ? 2 : 1;
	while ((cmds = cmds->next))
	{
		if ((type = type_params(cmds->token)))
			*info_params += byte_info_params(file, cmds, info, type);
		else
			print_error_token(file, cmds, SYNTAX_MSG);
		result += size_params(info, type);
		cmds = cmds->next;
		if (stop_params(file, cmds, info))
			break ;
	}
	cmds = cmds->start;
	return (result);
}

int		parser_instruction(t_line *file, t_cmd *cmds)
{
	int result;

	result = 0;
	cmds = (cmds->token == LABEL) ? cmds->next : cmds;
	if (cmds->token == ENDLINE ||
		cmds->token == COMMAND_NAME ||
		cmds->token == COMMAND_COMMENT)
		return (0);
	if (cmds->token == INSTRUCTION)
	{
		if ((instruction_exist(cmds->data)).name)
			result = parser_params(file, cmds, (&cmds->info));
		else
			print_error_token(file, cmds, INVALID_INSTRUCTION_MSG);
	}
	else
		print_error_token(file, cmds, SYNTAX_MSG);
	return (result);
}

void	parser_code(t_line *file)
{
	t_line	*tmp;
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line;
		while (ptr)
		{
			if (ptr->token == END && ptr->prev)
				print_error_token(file, ptr, SYNTAX_MSG);
			if (ptr->token == COMMAND_NAME || ptr->token == COMMAND_COMMENT)
				print_error_token(file, ptr, SYNTAX_MSG);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}
