/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:54:45 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 18:57:12 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

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

int		main(int argc, char const *argv[])
{
	t_cmd	*pointer;
	int		fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (0);
		if (!(pointer = reader(0, fd)))
			printf("ERROR");
		else
			printf("\nLAAA-> %s\n", pointer->data);
		free_list(pointer);
	}
	return (0);
}
