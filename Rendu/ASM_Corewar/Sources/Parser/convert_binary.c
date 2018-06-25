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

int 	has_arg(char args, int query)
{
	return (args & query);
}

int		token_instruction(int token)
{
	if (token == REGISTER)
		return (1);
	if (token == DIRECT || token == DIRECT_LABEL)
		return (2);
	if (token == INDIRECT || token == INDIRECT_LABEL)
		return (3);
	return (0);
}

int		end_instruction(t_line *file, t_cmd *result, t_op info, int *cur)
{
	if (info.params[++(*cur)])
	{
		if (result->token != SEPARATOR)
			print_error_token(file, result, SYNTAX_MSG);
		return (0);
	}
	else
		if (result->token != ENDLINE)
			print_error_token(file, result, SYNTAX_MSG);
	return (1);
}


int		test_cmd(t_line *file, t_cmd *result, t_op info, int type)
{
	static int	test = 8;
	static int	cur = 0;
	int			ret = 0;

	if (has_arg(info.params[cur++], ((type == 3) ? 4 : type)))
		ret = (type << (test -= 2));
	else
		print_error_params(file, result, cur - 1, type);
	if (!(info.params[cur]) && (test = 8))
		cur = 0;
	return (ret);
}

int		size_params(t_op info, int type)
{
	if (type == 1)
		return (1);
	if (type == 2)
	{
		if (info.size_dir)
			return (2);
		else
			return (4);
	}
	if (type == 3)
		return (2);
	return (0);
}

int		fill_binary_cmd(t_line *file, t_cmd *result, t_op info, int *ptr)
{
	int cur_params;
	int ret;
	int ret_2;

	ret_2 = 0;
	cur_params = 0;
	while (1)
	{
		if ((ret = token_instruction(result->token)))
			*ptr += test_cmd(file, result, info, ret);
		else
			print_error_token(file, result, SYNTAX_MSG);
		ret_2 += size_params(info, ret);
		result = result->next;
		if (end_instruction(file, result, info, &cur_params))
			break;
		result = result->next;
	}
	result = result->start;
	return (ret_2 + 1 + info.info_params);
}

void	count_octet(t_line *file, t_cmd *result)
{
	t_op	info;

	result = (result->token == LABEL) ? result->next : result;
	if (result->token == ENDLINE || result->token == COMMAND_NAME ||
		result->token == COMMAND_COMMENT)
		return ;
	if (result->token == INSTRUCTION)
	{	
		if ((info = cmd_exist(result->data)).name)
			result->octet = fill_binary_cmd(file, result->next, info, (&result->info));
		else
			print_error_token(file, result, INVALID_INSTRUCTION_MSG);
	}
	else
		print_error_token(file, result, SYNTAX_MSG);
}
