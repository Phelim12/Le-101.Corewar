/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_asm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 20:24:14 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 20:24:14 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_error_size_code(t_line *file)
{
	ft_putstr_fd(MSG_SIZE, 2);
	ft_putnbr_fd(CHAMP_MAX_SIZE, 2);
	ft_putendl_fd(")", 2);
	free_file(file);
	exit(EXIT_FAILURE);
}

void	print_error_lexical(t_line *result, t_pos position)
{
	free_file(result);
	ft_putstr_fd(MSG_LEXICAL, 2);
	ft_putnbr_fd(position.y, 2);
	ft_putchar_fd(':', 2);
	ft_putnbr_fd(position.x, 2);
	ft_putendl_fd("]", 2);
	exit(EXIT_FAILURE);
}

void	print_error_size_header(t_line *file, char *cmd, int size)
{
	ft_putstr_fd(MSG_HEADER_1, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(MSG_HEADER_2, 2);
	ft_putnbr_fd(size, 2);
	ft_putchar_fd(')', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
	exit(EXIT_FAILURE);
}

void	print_error_params(t_line *file, t_cmd *params, int nb, int type)
{
	t_cmd *ptr;

	ptr = params;
	while (ptr->token != INSTRUCTION)
		ptr = ptr->prev;
	ft_putstr_fd(MSG_PARAMS_1, 2);
	ft_putnbr_fd(nb, 2);
	ft_putstr_fd(MSG_PARAMS_2, 2);
	if (type == 1)
		ft_putstr_fd(MSG_REG, 2);
	if (type == 2)
		ft_putstr_fd(MSG_DIR, 2);
	if (type == 3)
		ft_putstr_fd(MSG_REG, 2);
	ft_putstr_fd(MSG_PARAMS_3, 2);
	ft_putendl_fd(ptr->data, 2);
	free_file(file);
	exit(EXIT_FAILURE);
}
