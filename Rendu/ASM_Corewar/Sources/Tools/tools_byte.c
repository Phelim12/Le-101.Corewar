/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_byte.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 17:46:47 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 17:46:47 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		type_params(int token)
{
	if (token == REGISTER)
		return (T_REG);
	if (token == DIRECT || token == DIRECT_LABEL)
		return (T_DIR);
	if (token == INDIRECT || token == INDIRECT_LABEL)
		return (T_IND);
	return (0);
}

int		code_params(int type)
{
	if (type == T_DIR)
		return (DIR_CODE);
	if (type == T_IND)
		return (IND_CODE);
	if (type == T_REG)
		return (REG_CODE);
	return (0);
}

int		size_params(t_op info, int type)
{
	if (type == T_REG)
		return (REG_SIZE);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR && info.size_dir)
		return (IND_SIZE);
	if (type == T_DIR && !(info.size_dir))
		return (DIR_SIZE);
	return (0);
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
