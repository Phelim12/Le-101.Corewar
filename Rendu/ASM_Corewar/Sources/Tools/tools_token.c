/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_token.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 17:48:41 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 17:48:41 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

char	*token_name(int token)
{
	if (token == REGISTER)
		return ("REGISTER");
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
	return ("END");
}

int		token_dispenser(char *cmd, char *buf, int string)
{
	if (string && (*buf) == CHAR_STRING)
		return (STRING);
	if (cmd[0] == CHAR_EOF || cmd[0] == CHAR_LINE)
		return ((cmd[0] == CHAR_EOF) ? END : ENDLINE);
	if (cmd[0] == 'r' && ft_strisdigit(cmd + 1) &&
		ft_atoi(cmd + 1) > 0 && ft_atoi(cmd + 1) < 17)
		return (REGISTER);
	if (cmd[0] == CHAR_LABEL)
		return (INDIRECT_LABEL);
	if (ft_strstr(cmd, "%:"))
		return (DIRECT_LABEL);
	if (ft_strchr(cmd, CHAR_LABEL))
		return (LABEL);
	if (cmd[0] == CHAR_DIRECT)
		return (DIRECT);
	if (cmd[0] == CHAR_SEPARATOR && !(cmd[1]))
		return (SEPARATOR);
	if (ft_strispattern(cmd, CHARS_DIRECT))
		return (INDIRECT);
	if (!(ft_strcmp(cmd, CMD_NAME)))
		return (COMMAND_NAME);
	if (ft_strispattern(cmd, CHARS_INSTRUCTION))
		return (INSTRUCTION);
	return (!(ft_strcmp(cmd, CMD_COMMENT)) ? COMMAND_COMMENT : END);
}
