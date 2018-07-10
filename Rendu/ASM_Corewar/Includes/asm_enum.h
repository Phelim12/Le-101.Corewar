/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_enum.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 19:04:15 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 19:04:15 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_ENUM_H
# define ASM_ENUM_H

typedef enum		e_msg
{
	SYNTAX_MSG,
	DUP_LABEL_MSG,
	NOT_EXIST_LABEL_MSG,
	INVALID_INSTRUCTION_MSG,
}					t_msg;

typedef enum		e_token
{
	END,
	LABEL,
	DIRECT,
	STRING,
	ENDLINE,
	INDIRECT,
	REGISTER,
	SEPARATOR,
	INSTRUCTION,
	DIRECT_LABEL,
	COMMAND_NAME,
	INDIRECT_LABEL,
	COMMAND_COMMENT,
}					t_token;

#endif
