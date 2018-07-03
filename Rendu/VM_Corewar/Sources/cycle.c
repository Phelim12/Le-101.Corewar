/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cycle.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 11:38:10 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/03 11:39:15 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int		cycle_process()
{
	t_process *proc;

	proc = get_last_proc(); //on chope le processus a exec en premier (la liste est dans l'ordre ?)
	while (proc)
	{
		if (!proc->cycle_delay)
			proc->fetchqueue = read_instruction(); //jump au prochain op puis read l'instruction + le bit d'encodage et on l'insere dans la fetchqueue
		else
			proc->cycle_delay--;
		proc = proc->next;
	}
	return (0);
}
/*
int		read_instruction();
{}
*/
