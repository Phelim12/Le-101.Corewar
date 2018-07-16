/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: magaspar <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 16:50:18 by magaspar     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 17:48:55 by magaspar    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void	ft_add(t_process **proc, t_vm *g_vm)
{
	if ((*proc)->registers[(*proc)->fetchqueue[0][1]] &&
			(*proc)->registers[(*proc)->fetchqueue[0][2]] &&
			(*proc)->registers[(*proc)->fetchqueue[0][3]])
	{
		(*proc)->registers[(*proc)->fetchqueue[0][3]] =
			(*proc)->registers[(*proc)->fetchqueue[0][3]]
			+ (*proc)->registers[(*proc)->fetchqueue[0][3]];
	}
}

/*Need to add convertion des registres*/
