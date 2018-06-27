/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rabbit_run.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 14:46:51 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 12:02:25 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static int check_players_process()
{
	int	a;
	int	nb;

	a = -1;
	nb = 0;
	while (++a < g_vm->nb_players)
		nb += g_vm->champion[a]->nb_process;
	return (nb);
}

int		cycling(void)
{

	while (check_players_process() > 0)
	{
		//check_destruction_process(); //mdr -> pour detruire un process, il faut l'enlever de la memoire, et du tableau double.
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
	}
	return (0);
}
