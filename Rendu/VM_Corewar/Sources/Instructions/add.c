/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 15:08:51 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:20:53 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

void		ft_add(t_process **proc)
{
	(*proc)->registers[(*proc)->params[2][1]] =
		((*proc)->registers[(*proc)->params[0][1]] +
		(*proc)->registers[(*proc)->params[1][1]]);
	(*proc)->carry = (!(*proc)->registers[(*proc)->params[2][1]] ? 1 : 0);
}
