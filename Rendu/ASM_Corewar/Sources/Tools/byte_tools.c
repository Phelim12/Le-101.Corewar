/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   byte_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/28 15:48:44 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 15:48:44 by clcreuso    ###    #+. /#+    ###.fr     */
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