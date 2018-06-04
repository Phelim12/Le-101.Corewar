/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 14:36:39 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int		main(int argc, char const **argv)
{
	if (argc > 1)
	{
		init_vm(argv);
		parse_args(argv);
		//save_champs(); // need to interpret .cor files ?
		//init_map(); //full 0, map de MEM_SIZE, init nb_players * 16 registres
		//load_champs(); //divide map in nb_players and load them -> need to interpret .cor files
		//RUN();
	}
	else
		print_usage();
	return (0);
}
