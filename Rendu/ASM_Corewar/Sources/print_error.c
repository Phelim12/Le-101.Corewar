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

void	print_error_malloc_fail(t_line *file)
{
	ft_putendl_fd("asm: Failed to allocate memory.", 2);
	free_file(file);
	exit(EXIT_FAILURE);
}

void	print_error_lexical(t_line *result, t_pos position)
{
	free_file(result);
	ft_putstr_fd("Lexical error at [", 2);
	ft_putnbr_fd(position.y, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(position.x, 2);
	ft_putendl_fd("]", 2);
	exit(EXIT_FAILURE);
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

void	print_error_msg(t_cmd *cmd, int msg_error)
{
	if (msg_error == SYNTAX_MSG)
		ft_putstr_fd("Syntax error at token [TOKEN][", 2);
	if (msg_error == DUP_LABEL_MSG)
		ft_putstr_fd("The label already exists at [TOKEN][", 2);
	if (msg_error == NOT_EXIST_LABEL_MSG)
	{
		ft_putstr_fd("No such label ", 2);
		if (cmd->token == DIRECT_LABEL)
			ft_putstr_fd((cmd->data + 2), 2);
		if (cmd->token == INDIRECT_LABEL)
			ft_putstr_fd((cmd->data + 1), 2);
		ft_putstr_fd(" while attempting to dereference token [TOKEN][", 2);
	}
	if (msg_error == INVALID_INSTRUCTION_MSG)
		ft_putstr_fd("Invalid instruction at token [TOKEN][", 2);
}

void	print_error_token(t_line *file, t_cmd *cmd, int msg_error)
{
	print_error_msg(cmd, msg_error);
	print_coord_token(cmd->pos.y, 2);
	ft_putchar_fd(':', 2);
	print_coord_token(cmd->pos.x, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(token_name(cmd->token), 2);
	ft_putchar_fd(' ', 2);
	if (cmd->token == STRING)
		ft_putchar_fd('"', 2);
	if (cmd->token != ENDLINE)
		ft_putchar_fd('"', 2);
	if (cmd->data[0] > 32)
		ft_putstr_fd(cmd->data, 2);
	if (cmd->token == END)
		ft_putstr_fd("(null)", 2);
	if (cmd->token != ENDLINE)
		ft_putchar_fd('"', 2);
	if (cmd->token == STRING)
		ft_putchar_fd('"', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
	exit(EXIT_FAILURE);
}
