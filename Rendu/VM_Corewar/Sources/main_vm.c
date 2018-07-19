/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 12:30:54 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int		main(int argc, char const **argv)
{
//	int	*tmp;
//	t_process *list_tmp;

	if (argc > 1)
	{
		init_vm(argv);
		check_data();
//		int k = (int)extract(g_vm->map + 1, 2, 12, MEM_SIZE); //TEST
//		ft_printf("|| This is it : %b and : %d||\n", k, k); // TEST
		cycling();
/*		ft_printf("ctd\t: %20d\ncycle\t: %20d\ndump\t: %20d\nd_cycles : %20d\nnb_players : %20d\n////////\n",
				g_vm->cycle_to_die, g_vm->cycle, g_vm->dump, g_vm->d_cycles, g_vm->nb_players);
		int	i = g_vm->nb_players;
		list_tmp = g_vm->list_process;
		while (--i >= 0)
		{
			tmp = list_tmp->registers;
			ft_printf("filename\t: %20s\nlive\t\t: %20d\nnb_process\t: %20d\nname\t\t: %20s\ncomment\t\t: %20s\nnum\t\t: %20d\nPC\t\t: %20d\nsize\t\t: %20u\nmagic\t\t: %20u\n---------\n",
					g_vm->champion[i]->filename, g_vm->champion[i]->live,
					g_vm->champion[i]->nb_process, g_vm->champion[i]->name,
					g_vm->champion[i]->comment, tmp[1],
					tmp[0], g_vm->champion[i]->prog_size,
					g_vm->champion[i]->magic);
			list_tmp = list_tmp->next;
		}*/
	ft_printf("le joueur %d(%s) a gagne\n", g_vm->last_live, g_vm->champion[g_vm->last_live]->name);
	}
	else
		print_usage();
	return (0);
}
