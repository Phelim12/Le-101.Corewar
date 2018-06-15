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

void	print_error_reader(t_line *result, t_pos position)
{
	if (result)
		result = result->start;
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

void	print_error_token(t_line *file, t_cmd *line, char *name)
{
	ft_putstr_fd("Syntax error at token [TOKEN][", 2);
	ft_putnbr_pad3_fd(line->pos.y, 2);
	ft_putchar_fd(':', 2);
	if (!(ft_strcmp(name, "ENDLINE")))
		ft_putnbr_pad3_fd((line->pos.x + ft_strlen(line->data) + 1), 2);
	else
		ft_putnbr_pad3_fd(line->pos.x, 2);
	ft_putstr_fd("] ", 2);
	if (line->token)
		ft_putchar_fd('"', 2);
	ft_putstr_fd(name, 2);
	if (line->token)
		ft_putchar_fd('"', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
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