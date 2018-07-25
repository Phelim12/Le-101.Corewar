/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rabbit_run.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 14:46:51 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 01:10:26 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static	int check_players_process()
{
	int				nb;
	t_process		*proc;

	proc = g_vm->list_process;
	nb = 0;
	while (proc)
	{
		nb += 1;
		proc = proc->next;
	}
//	dprintf(2, "nb_process : %d\n", nb);
	return (nb);
}

static int		check_destruction_process(int cycles_passed)
{
	if (cycles_passed + 1 == g_vm->cycle_to_die)
	{
		g_vm->checks++;
		if (process_remove_if_live(&g_vm->list_process, 0) >= NBR_LIVE || g_vm->checks >= MAX_CHECKS)
		{
			g_vm->cycle_to_die -= CYCLE_DELTA;
			g_vm->checks = 0;
		}
		cycles_passed = 0;
	}
	return (cycles_passed);
}

static int		increment(cycles_passed)
{
	g_vm->cycle++;
	cycles_passed++;
	return (cycles_passed);
}

static char		*get_champ_name(int player)
{
	int		i;

	i = -1;
	if (player < 0)
		return (NULL);
	while (++i < g_vm->nb_players)
		if (g_vm->champion[i]->num == player)
			return (g_vm->champion[i]->name);
	return (NULL);
}

int		cycling(void)
{
	unsigned int	cycles_passed;
	int				win;

	win = 0;
	introduction();
	cycles_passed = 0;
	while (check_players_process() > 0 &&
			(g_vm->dump == 0 || g_vm->cycle <= g_vm->d_cycles))
	{
		if (g_vm->v >= 3)
			ft_printf("\nCycle %d\n", g_vm->cycle);
		lets_process();
		cycles_passed = check_destruction_process(cycles_passed);
		if (!check_players_process())
			break ;
		cycles_passed = increment(cycles_passed);
//		dprintf(2, "cycle_passed %d\n cycle_to_die %u\n", cycles_passed, g_vm->cycle_to_die);
//		dprintf(2, "Player %d last_lived\n----------------------------------------------------\n\n", g_vm->last_live);
		
	}
//	dprintf(2, "cycles = %d\n", g_vm->cycle);
	if (g_vm->dump == 1 && g_vm->cycle > g_vm->d_cycles)
		ft_dump();
	else
	{
		if (g_vm->last_live < 0)
			win = g_vm->nb_players - 1;
		else
			win = g_vm->last_live;
		ft_printf("Contestant %d, \"%s\", has won !\n", g_vm->champion[win]->num, g_vm->champion[win]->name);
	}
	return (0);
}

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃
**┃ ------ Le Pole Question
**┃
**┃ - Lors de l'arrivee sur une instruction viable, parser l'instruction et la stocker dans la fetchqueue ?
**┃ ----> Comportement a verifier par corruption de l'instruction pendant le delay
**┃ - Lors de l'arrivee sur une instruction viable, garder en memoire les valeurs
**┃ des variables pouvant etre ecrasee ?
**┃ ----> Comportement a verifier par corruption des valeurs pendant le delay
**┃ ----> Il est vraisemblable que ce sera lors de l'exec que l'on ira chercher les valeurs des parametres
**┃
**┃ - Mouvement du PC. A mon avis : PC bouge a chaque instruction, jump s'il faut jump etc.
**┃ Le curseur visible de la VM n'est pas le PC, mais un vrai cursor en recherche de la prochaine instruction.
**┃ Sur ..|00|.. c'est le cursor qui se deplace, et le PC est laisse avant.
**┃ Je pense qu'il faudrait suivre le verbose 16 de la VM dans un premier temps
**┃ Maybe.
**┃ ----> a confirmer
**┃	/!\ SEGV sur ./corewar -d 1500 --> SOLVED (pb lors de l'init et le free_all, des trucs pas instancies)
**┃
**┃ LEAKS ?
**┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

