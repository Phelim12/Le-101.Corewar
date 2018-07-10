/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_token.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 20:05:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 20:05:59 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_coord_token(int nbr, int fd)
{
	if (nbr < 100)
		ft_putchar_fd('0', fd);
	if (nbr < 10)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(nbr, fd);
}

void	print_error_msg(t_cmd *cmd, int msg_error)
{
	if (msg_error == SYNTAX_MSG)
		ft_putstr_fd(MSG_SYNTAX, 2);
	if (msg_error == DUP_LABEL_MSG)
		ft_putstr_fd(MSG_LABEL_1, 2);
	if (msg_error == NOT_EXIST_LABEL_MSG)
	{
		ft_putstr_fd(MSG_LABEL_2, 2);
		if (cmd->token == DIRECT_LABEL)
			ft_putstr_fd((cmd->data + 2), 2);
		if (cmd->token == INDIRECT_LABEL)
			ft_putstr_fd((cmd->data + 1), 2);
		ft_putstr_fd(MSG_LABEL_3, 2);
	}
	if (msg_error == INVALID_INSTRUCTION_MSG)
		ft_putstr_fd(MSG_INSTRUCTION, 2);
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
