/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_binary.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 19:45:41 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/24 19:45:41 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		end_instruction(t_line *file, t_cmd *result, t_op info)
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

int		byte_info_params(t_line *file, t_cmd *cmd, t_op info, int type)
{
	static int	bit_shift = 8;
	static int	index = 0;
	int			byte;
	int			code;

	byte = 0;
	code = code_params(type);
	if (has_arg(info.params[index++], type))
		byte = (code << (bit_shift -= 2));
	else
		print_error_params(file, cmd, index - 1, type);
	if (!(info.params[index]) && (bit_shift = 8))
		index = 0;
	return (byte);
}

int		count_byte_params(t_line *file, t_cmd *cmds, int *info_params)
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
		if (end_instruction(file, cmds, info))
			break;
	}
	cmds = cmds->start;
	return (result);
}

int		count_byte_instruction(t_line *file, t_cmd *cmds)
{
	int result;

	result = 0;
	cmds = (cmds->token == LABEL) ? cmds->next : cmds;
	if (cmds->token == ENDLINE || cmds->token == COMMAND_NAME ||
		cmds->token == COMMAND_COMMENT)
		return (0);
	if (cmds->token == INSTRUCTION)
	{	
		if ((instruction_exist(cmds->data)).name)
			result = count_byte_params(file, cmds, (&cmds->info));
		else
			print_error_token(file, cmds, INVALID_INSTRUCTION_MSG);
	}
	else
		print_error_token(file, cmds, SYNTAX_MSG);
	return (result);
}
