/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_asm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:53:36 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 15:16:51 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"

t_pos	init_pos(int y, int x)
{
	t_pos	result;

	result.x = x;
	result.y = y;
	return (result);
}

void	free_line(t_cmd *line)
{
	t_cmd	*ptr;

	while (line)
	{
		ptr = line;
		free(line->data);
		line = line->next;
		free(ptr);
	}
}

void	free_file(t_line *file)
{
	t_line	*ptr;

	while (file)
	{
		ptr = file;
		free_line(file->line);
		file = file->next;
		free(ptr);
	}
}

void	print_line(t_cmd *pointer)
{
	while (pointer)
	{
		ft_printf("[%s] ", pointer->data);
		pointer = pointer->next;
	}
	ft_printf("\n");
}

void	print_file(t_line *pointer)
{
	while (pointer)
	{
		ft_printf("LINE = ");
		print_line(pointer->line);
		pointer = pointer->next;
	}
}
