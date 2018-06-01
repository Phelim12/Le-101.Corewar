/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_vm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 15:43:36 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 15:48:49 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

void	print_usage(void)
{
	ft_printf(USE);
}

void	ft_error(char *s)
{
	int i;

	i = 0;
	while (i < g_vm->nb_players)
		free(g_vm->champions[i++]);
	free(g_vm->champions);
	free(g_vm->num_champs);
	free(g_vm);
	ft_printf(s);
	exit(1);
}
