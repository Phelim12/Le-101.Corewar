/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_asm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:53:36 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/09 18:53:36 by clcreuso    ###    #+. /#+    ###.fr     */
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

void	free_list(t_cmd *list)
{
	t_cmd	*save;

	while (list)
	{
		save = list;
		free(list->data);
		list = list->next;
		free(save);
	}
}
