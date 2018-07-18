/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_add.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: magaspar <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 16:50:18 by magaspar     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 14:34:17 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

void	ft_add(t_process **proc)
{
	if ((*proc)->registers[(*proc)->fetchqueue[0][0]] &&
			(*proc)->registers[(*proc)->fetchqueue[1][0]] &&
			(*proc)->registers[(*proc)->fetchqueue[2][0]])
	{
		(*proc)->registers[(*proc)->fetchqueue[2][1]] =
			(*proc)->registers[(*proc)->fetchqueue[0][1]]
			+ (*proc)->registers[(*proc)->fetchqueue[1][1]];
	}
}

/*Need to add convertion des registres*/
