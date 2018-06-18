/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_dispenser.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 19:06:54 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 19:06:54 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

char	*token_name(int token)
{
	if (token == END)
		return ("END");
	if (token == LABEL)
		return ("LABEL");
	if (token == DIRECT)
		return ("DIRECT");
	if (token == STRING)
		return ("STRING");
	if (token == ENDLINE)
		return ("ENDLINE");
	if (token == INDIRECT)
		return ("INDIRECT");
	if (token == SEPARATOR)
		return ("SEPARATOR");
	if (token == INSTRUCTION)
		return ("INSTRUCTION");
	if (token == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	if (token == COMMAND_NAME)
		return ("COMMAND_NAME");
	if (token == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	if (token == COMMAND_COMMENT)
		return ("COMMAND_COMMENT");
	return ("");
}

int		token_dispenser(char *cmd, char buf)
{
	if (cmd[0] == LINE_CHAR)
		return (ENDLINE);
	if (buf == STRING_CHAR)
		return (STRING);
	if (cmd[0] == EOF_CHAR)
		return (END);
	if (cmd[0] == LABEL_CHAR)
		return (INDIRECT_LABEL);
	if (ft_strstr(cmd, "%:"))
		return (DIRECT_LABEL);
	if (ft_strchr(cmd, LABEL_CHAR))
		return (LABEL);
	if (cmd[0] == DIRECT_CHAR)
		return (DIRECT);
	if (cmd[0] == SEPARATOR_CHAR && !(cmd[1]))
		return (SEPARATOR);
	if (ft_strispattern(cmd, DIRECT_CHARS))
		return (INDIRECT);
	if (!(ft_strcmp(cmd, CMD_NAME)))
		return (COMMAND_NAME);
	if (ft_strispattern(cmd, INSTRUCTION_CHARS))
		return (INSTRUCTION);
	if (!(ft_strcmp(cmd, CMD_COMMENT)))
		return (COMMAND_COMMENT);
	return (0);
}
