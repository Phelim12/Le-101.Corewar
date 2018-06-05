/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:43:36 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 17:19:37 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

void	print_usage(void)
{
	ft_printf(USE1);
	ft_printf(USE2);
	ft_printf(USE3);
}

void	ft_error(char *s)
{
	unsigned int i;

	i = 0;
	while (i < g_vm->nb_players)
		free(g_vm->champion[i++]);
	free(g_vm->champion);
	free(g_vm);
	ft_printf(s);
	exit(1);
}
