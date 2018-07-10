/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 11:20:48 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int		cycle_process()
{
	t_process	*proc;

	proc = g_vm->list_process;
	while (proc)
	{
		if (!proc->cycle_delay && !proc->fetchqueue)
		{
//			proc->fetchqueue = read_instruction(); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		}
		else if (!proc->cycle_delay && proc->fetchqueue)
		{
			//exec_process();
		}
		else
			proc->cycle_delay--;
	}
	return (0);
}

/*
unsigned char	*read_instruction()
{

}

void			*exec_process()
{

}
*/
