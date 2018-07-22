/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 17:33:45 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:18:46 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int			init_process(unsigned int a)
{
	int				*tmp_reg;
	t_process		*new;

	if (!(tmp_reg = (int*)malloc(REG_SIZE * (REG_NUMBER + 1))))
		return (-1);
	else
	{
		ft_memset(tmp_reg, 0, (REG_NUMBER + 1) * REG_SIZE);
		tmp_reg[1] = -g_vm->champion[a]->num;
		tmp_reg[0] = a * MEM_SIZE / g_vm->nb_players;
		tmp_reg[15] = 0;
//		dprintf(2, "reg[16] = %d\n", tmp_reg[15]);
		new = lstnew_vm(tmp_reg, REG_SIZE * (REG_NUMBER + 1));
		new->cycle_delay = -1;
		if (g_vm->list_process == NULL)
			g_vm->list_process = new;
		else
			lstadd_vm(&g_vm->list_process, new);
		free(tmp_reg);
	}
	return (0);
}

static void	sort_champ_tab(void)
{
	t_champ			*tmp;
	unsigned int	i;

	i = -1;
	while (++i < g_vm->nb_players - 1)
	{
		if (g_vm->champion[i]->num > g_vm->champion[i + 1]->num)
		{
			tmp = g_vm->champion[i];
			g_vm->champion[i] = g_vm->champion[i + 1];
			g_vm->champion[i + 1] = tmp;
			i = -1;
		}
	}
}

static int	sub2_init_champ(void)
{
	int	a;

	a = g_vm->nb_players;
	sort_champ_tab();
	while (--a >= 0)
		if (init_process(a) == -1 || get_champ(a) == -1)
			return (-1);
	return (0);
/*	unsigned int	a;

	a = -1;
	sort_champ_tab();
	while (++a < g_vm->nb_players)
		if (init_process(a) == -1 || get_champ(a) == -1)
			return (-1);
	return (0);*/
}

static void	sub_init_champ(void)
{
	unsigned int	i;
	long			num;
	unsigned int	j;
	unsigned int	f;

	i = -1;
	num = 1;
	while (++i < g_vm->nb_players)
	{
		g_vm->champion[i]->live = 0;
		g_vm->champion[i]->nb_process = 1;
		f = 1;
		while (g_vm->champion[i]->num == 0)
		{
			j = -1;
			while (++j < g_vm->nb_players)
				if ((long)g_vm->champion[j]->num == (long)num)
					f = 0;
			if (f == 0)
				num++;
			else
				g_vm->champion[i]->num = (long)num;
		}
		num++;
	}

/*	i = -1;
	num = 1;
	while (++i < g_vm->nb_players)
	{
		g_vm->champion[i]->live = 0;
		g_vm->champion[i]->nb_process = 1;
		if (g_vm->champion[i]->num == 0)
		{
			j = -1;
			while (++j < g_vm->nb_players)
			{
				if (g_vm->champion[j]->num == num)
				{
					num++;
					j = -1;
				}
			}
			g_vm->champion[i]->num = -num++;
		}
	}*/

	sub2_init_champ();
}

void		init_champs(char const **argv)
{
	void			*tmp;
	unsigned int	i;

//	dprintf(1, "in init champs\n");
	i = 0;
	while (argv[i])
	{
		if (!ft_strcmp(".cor", &argv[i][ft_strlen(argv[i]) - 4]))
			g_vm->nb_players++;
		i++;
	}
	i = 0;
	if ((tmp = (t_champ**)malloc(sizeof(t_champ*) * g_vm->nb_players + 1)))
		g_vm->champion = tmp;
	while (i < g_vm->nb_players)
	{
		if ((tmp = (t_champ*)malloc(sizeof(t_champ))))
			g_vm->champion[i] = tmp;
		g_vm->champion[i++]->num = 0;
	}
	if (g_vm->nb_players > MAX_PLAYERS)
		error_vm("Too many .cor files in parameters\n", 0);
	parse_args(argv);
	sub_init_champ();
}

int			init_map(void)
{
	t_process		*list_tmp;
	int				*tmp;
	unsigned int	i;

	i = 0;
	if (!(g_vm->map = malloc(MEM_SIZE + 1)) || !(g_vm->p_map = malloc(MEM_SIZE + 1)))
		return (-1);
	g_vm->map[MEM_SIZE] = '\0';
	g_vm->p_map[MEM_SIZE] = '\0';
	g_vm->map = ft_memset(g_vm->map, 0, (size_t)MEM_SIZE);
	g_vm->p_map = ft_memset(g_vm->p_map, -1, (size_t)MEM_SIZE);
	list_tmp = g_vm->list_process;
	while (list_tmp)
	{
		tmp = list_tmp->registers;
		ft_memcpy(&g_vm->map[tmp[0]],
				g_vm->champion[i]->instructions, g_vm->champion[i]->prog_size);
		ft_memset(&g_vm->p_map[tmp[0]],
				tmp[1], g_vm->champion[i]->prog_size);
		list_tmp = list_tmp->next;
		i++;
	}
	return (0);
}

void		init_vm(char const **argv)
{
	void	*tmp;

	if ((tmp = (t_vm*)malloc(sizeof(t_vm))))
		g_vm = tmp;
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->cycle = 0;
	g_vm->checks = 0;
	g_vm->champion = NULL;
	g_vm->list_process = NULL;
	g_vm->map = NULL;
	g_vm->p_map = NULL;
	g_vm->last_live = -1;
	g_vm->dump = 0;
	g_vm->v = 0;
	g_vm->d_size = 0;
	g_vm->d_cycles = 0;
	g_vm->nb_players = 0;
	init_champs(argv);
	init_map();
/*	unsigned int x = -1;
	dprintf(1, "nb_players = %d\n", g_vm->nb_players);
	while (++x < g_vm->nb_players)
	{
		dprintf(1, "champion_num = %d\n name : %s\n", g_vm->champion[x]->num, g_vm->champion[x]->name);
	}
	t_process *proc;
	proc = g_vm->list_process;
	while (proc)
	{
		dprintf(1, "PC : %d\n num : %d\n", proc->registers[0], proc->registers[1]);
		proc = proc->next;
	}
*/}
