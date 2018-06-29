/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 21:55:04 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 21:55:04 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

/*
** DEBUG
*/

void	print_line(t_cmd *pointer)
{
	while (pointer)
	{
		if (pointer->token == ENDLINE)
			ft_printf("\n", pointer->data);
		else
			ft_printf("[%s] %s", pointer->data, token_name(pointer->token));
		pointer = pointer->next;
	}
}

void	print_file(t_line *pointer)
{
	while (pointer)
	{
		print_line(pointer->line);
		pointer = pointer->next;
	}
	ft_printf("\n");
}
