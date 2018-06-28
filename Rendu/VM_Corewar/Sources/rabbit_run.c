/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rabbit_run.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 14:46:51 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 13:08:10 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static	int check_players_process()
{
	unsigned int	a;
	int				nb;

	a = -1;
	nb = 0;
	while (++a < g_vm->nb_players)
		nb += g_vm->champion[a]->nb_process;
	return (nb);
}

static int		check_destruction_process(int cycles_passed)
{
	if (cycles_passed == g_vm->cycle_to_die)
	{
		g_vm->checks++;
		if (process_remove_if_live(&g_vm->list_process, 0) >= NBR_LIVE || g_vm->checks >= MAX_CHECKS)
		{
			g_vm->cycle_to_die -= CYCLE_DELTA;
			g_vm->checks = 0;
		}
		cycles_passed = 0;
		// va parcourir la liste des processes et checker s'ils ont bien dit etre en vie (sinon CIAO), return le nombre de lives et les reinitialise a 0.
		// s'il y a eu assez de lives on decremente CYCLE_TO_DIE.
	}
	return (cycles_passed);
}

static int		increment(cycles_passed)
{
	g_vm->cycle++;
	cycles_passed++;
	return (cycles_passed);
}

int		cycling(void)
{
	unsigned int cycles_passed;

	cycles_passed = 0;
	while (check_players_process() > 0 &&
			(g_vm->dump == 0 || g_vm->cycle < g_vm->d_cycles))
	{
		cycles_passed = check_destruction_process(cycles_passed); //mdr -> pour detruire un process, il faut l'enlever de la memoire, et du tableau double.
		//c'est qd meme plus pratique avec une liste chainees de process...
		//cycle_process(); //remplissage de la fetchqueue ou delai, ou exec d'autre chose qu'un fork ou un live ou une ecriture memoire
		//read_memory(); //stocker les infos en memoire. pourquoi pas carrement dupliquer g_vm avant et apres changement ? dans cycle_process ?
		//write_memory(); //si ecriture simultanee, parralelisme : le dernier process cree joue en premier.
			// /!\ /!\
			// /!\ /!\ les process sont tous stockes dans la vm, pas dans les champs.
			// /!\ /!\ On ne fait pas jouer un process d'un champ, puis un autre. a chaque cycle, tous les process jouent
			// /!\ /!\ D'ou le fait de les enregistrer ensembles dans la vm. inutile d'une struct champ pour les registers.
		//exec_fork();
		//exec_live();
		cycles_passed = increment(cycles_passed);
		dprintf(1, "cycle_passed %d\n cycle_to_die %u\n", cycles_passed, g_vm->cycle_to_die);
	}
	if (g_vm->dump == 1)
		ft_dump();
	return (0);
}
