/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   aff.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 14:00:35 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 14:05:37 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		debug_aff(char c)
{
	ft_printf("%c\n", c);
}

void		ft_aff(t_process **proc)
{
	char c;

	c = (*proc)->registers[(*proc)->fetchqueue[0][1]] % 256;
	if (c < 32 || c > 126)
		return ;
	debug_aff(c);
}
