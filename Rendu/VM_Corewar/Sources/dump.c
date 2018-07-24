/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 14:20:11 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 21:51:19 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

int		is_pc(int i)
{
	t_process	*tmp;

	tmp = g_vm->list_process;
	while (tmp)
	{
		if (i == tmp->registers[0])
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		print_color(int i, int *p, int pc)
{
	if (!(p[0] == g_vm->p_map[i] || p[1] == g_vm->p_map[i] || p[2] == g_vm->p_map[i] || p[3] == g_vm->p_map[i]))
	{
		if (!p[0])
			p[0] = g_vm->p_map[i];
		else if (!p[1])
			p[1] = g_vm->p_map[i];
		else if (!p[2])
			p[2] = g_vm->p_map[i];
		else if (!p[3])
			p[3] = g_vm->p_map[i];
	}
	if (g_vm->p_map[i] == p[0])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[1])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[2])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	if (g_vm->p_map[i] == p[3])
		ft_printf((pc ? "{n_white}{black}%02x{eoc}{eoc}" :
					"%02x"), g_vm->map[i]);
	return (0);
}

int		ft_print_pc(int pos)
{
	t_process		*tmp;
	int				tmp_player;

	tmp = g_vm->list_process;
	while (tmp)
	{
		/*ft_printf("TMP : %d\n", tmp->begin);
		  ft_printf("POS : %d\n", pos);
		// sleep(1);*/
		// ft_printf("ASDFADSFADSF = %d\t adfasdf ; %d\n", tmp->registers[0], pos);
		if (tmp->registers[0] == pos)
		{
			if (tmp->num == 1)
				ft_printf("\033[44m");
			if (tmp->num == 2)
				ft_printf("\033[41m");
			if (tmp->num == 3)
				ft_printf("\033[42m");
			if (tmp->num == 4)
				ft_printf("\033[43m");
			if (tmp->num == 5)
				ft_printf("\033[45m");
			if (tmp->num == 6)
				ft_printf("\033[46m");
			if (tmp->num == 7)
				ft_printf("\033[47m");
			if (tmp->num == 8)
				ft_printf("\033[48m");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		ft_dump(void)
{
	int i;
	int p[4];

	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;

	i = -1;

	while (++i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("%-#5.4x : ", i);
		else if (i % (g_vm->d_size ? g_vm->d_size : 64) == 0)
			ft_printf("\n%-#5.4x : ", i);
	//	if (ft_print_pc(i))
	//		ft_printf("%02x{eoc}", g_vm->map[i]);
	//	else
			ft_printf("%02x", g_vm->map[i]);
		ft_printf(" ");
	}
	ft_printf("\n");
	return (0);
}



























// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

