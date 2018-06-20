/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_label_error.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/15 17:02:57 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/15 17:02:59 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_error_malloc_fail(t_line *file, t_label *lab, t_cmd *cmd)
{
	ft_putstr_fd("Malloc failure at [TOKEN][", 2);
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
	free_label(lab);
	exit(EXIT_FAILURE);
}

void	print_error_label_repeat(t_line *file, t_cmd *cmd, t_label *lab)
{
	ft_putstr_fd("Label name repeated at [TOKEN][", 2);
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
	free_label(lab);
	exit(EXIT_FAILURE);
}

void	print_error_nolabel(t_line *file, t_cmd *cmd, t_label *lab)
{
	ft_putstr_fd("No such label ", 2);
	if (cmd->token == DIRECT_LABEL)
		ft_putstr_fd((cmd->data + 2), 2);
	else if (cmd->token == INDIRECT_LABEL)
		ft_putstr_fd((cmd->data + 1), 2);
	ft_putstr_fd(" while attempting to dereference token [TOKEN][", 2);
	print_coord_token(cmd->pos.y, 2);
	ft_putchar_fd(':', 2);
	print_coord_token(cmd->pos.x, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(token_name(cmd->token), 2);
	ft_putchar_fd(' ', 2);
	ft_putchar_fd('"', 2);
	ft_putstr_fd(cmd->data, 2);
	ft_putstr_fd("\"\n", 2);
	free_file(file);
	free_label(lab);
	exit(EXIT_FAILURE);
}
