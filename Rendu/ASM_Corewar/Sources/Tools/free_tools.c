/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 21:54:43 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 21:54:43 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	free_line(t_cmd *line)
{
	t_cmd	*ptr;

	line = (line) ? line->start : NULL;
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

	file = (file) ? file->start : NULL;
	while (file)
	{
		ptr = file;
		free_line(file->line);
		file = file->next;
		free(ptr);
	}
}
