/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 18:41:08 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int		print_map()
{
	int i;
	int p_one = -2;
	int p_two = -2;
	int p_three = -2;
	int p_four = -2;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (g_vm->p_map[i] < 0)
			ft_printf("%02x|", g_vm->map[i]);
		else
		{
			if (!(p_one == g_vm->p_map[i] || p_two == g_vm->p_map[i] || p_three == g_vm->p_map[i] || p_four == g_vm->p_map[i]))
			{
				if (p_one == -2)
					p_one = g_vm->p_map[i];
				else if (p_two == -2)
					p_two = g_vm->p_map[i];
				else if (p_three == -2)
					p_three = g_vm->p_map[i];
				else if (p_four == -2)
					p_four = g_vm->p_map[i];
			}
			if (g_vm->p_map[i] == p_one)
				ft_printf("{cyan}%02x{eoc}|", g_vm->map[i]);
			if (g_vm->p_map[i] == p_two)
				ft_printf("{yellow}%02x{eoc}|", g_vm->map[i]);
			if (g_vm->p_map[i] == p_three)
				ft_printf("{blue}%02x{eoc}|", g_vm->map[i]);
			if (g_vm->p_map[i] == p_four)
				ft_printf("{pink}%02x{eoc}|", g_vm->map[i]);
		}
	}
	return (0);
}

int		main(int argc, char const **argv)
{
	int	*tmp;
	t_process *list_tmp;

	if (argc > 1)
	{
		init_vm(argv);
		check_data();
		//		cycling();
		ft_printf("ctd\t: %20d\ncycle\t: %20d\ndump\t: %20d\nd_cycles : %20d\nnb_players : %20d\n////////\n",
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
		}
		print_map();
	}
	else
		print_usage();
	return (0);
}
