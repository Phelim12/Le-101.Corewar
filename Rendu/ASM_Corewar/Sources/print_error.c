/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 17:02:57 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:02:59 by clcreuso    ###    #+. /#+    ###.fr     */
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

void	print_error_size_header(t_line *file, char *cmd, int size)
{
	ft_putstr_fd("Champion ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" too long (Max length ", 2);
	ft_putnbr_fd(size, 2);
	ft_putchar_fd(')', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
	exit(EXIT_FAILURE);
}

void	print_error_reader(t_line *result, t_pos position)
{
	free_file(result);
	if (errno)
		perror("Error fd");
	else
	{
		ft_putstr_fd("Lexical error at [", 2);
		ft_putnbr_fd(position.y, 2);
		ft_putchar_fd(':', 2);
		ft_putnbr_fd(position.x, 2);
		ft_putendl_fd("]", 2);
	}
	exit(EXIT_FAILURE);
}

void	print_error_token(t_line *file, t_pos pos, char *name, int token)
{
	pos.x += (token == ENDLINE) ? (ft_strlen(name) + 1) : 0;
	pos.x += (token == STRING) ? -1 : 0;
	ft_putstr_fd("Syntax error at token [TOKEN][", 2);
	ft_putnbr_pad3_fd(pos.y, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_pad3_fd(pos.x, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(token_name(token), 2);
	ft_putstr_fd(" ", 2);
	if (token == STRING)
		ft_putchar_fd('"', 2);
	if (name && token != ENDLINE)
	{
		ft_putchar_fd('"', 2);
		ft_putstr_fd(name, 2);
		ft_putchar_fd('"', 2);
	}
	if (!name)
		ft_putstr_fd("\"(null)\"", 2);
	if (token == STRING)
		ft_putchar_fd('"', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
	exit(EXIT_FAILURE);
}
