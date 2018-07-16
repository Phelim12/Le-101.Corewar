/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sub.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: magaspar <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 17:49:21 by magaspar     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 17:50:14 by magaspar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void	ft_sub(t_process **proc, t_vm *g_vm)
{
	if ((*proc)->registers[(*proc)->fetchqueue[0][1]] &&
			(*proc)->registers[(*proc)->fetchqueue[0][2]] &&
			(*proc)->registers[(*proc)->fetchqueue[0][3]])
	{
		(*proc)->registers[(*proc)->fetchqueue[0][3]] =
			(*proc)->registers[(*proc)->fetchqueue[0][3]]
			- (*proc)->registers[(*proc)->fetchqueue[0][3]];
	}
}

/*Need to add convertion des registres*/
