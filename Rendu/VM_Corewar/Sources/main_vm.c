/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:38 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 19:44:46 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

int		main(int argc, char const **argv)
{
	if (argc > 1)
	{
		init_vm(argv);
		check_data();
		introduction();
		cycling();
		free_all();
	}
	else
		print_usage();
	return (0);
}
