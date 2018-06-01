/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:53 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 15:48:33 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAIN_VM
# define MAIN_VM
# define USE "Usage: ./corewar [-d N] [[-n number] \
champion1.cor] ...\n\t-d N\t: dump memory after nbr_cycles \
then exit\n\t-n number\t: set the number of the next player\n"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../../Libft/Includes/libft.h"
#include "../../Libft/Includes/ft_printf.h"

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃ Functions allowed:                                                         ┃
**┃  ◦ open                                                                    ┃
**┃  ◦ read                                                                    ┃
**┃  ◦ write                                                                   ┃
**┃  ◦ lseek                                                                   ┃
**┃  ◦ close                                                                   ┃
**┃  ◦ malloc                                                                  ┃
**┃  ◦ realloc                                                                 ┃
**┃  ◦ free                                                                    ┃
**┃  ◦ exit                                                                    ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct	s_vm
{
	int		dump;
	int		d_cycles;
	int		nb_players;
	int		*num_champs;
	char	**champions;
}				t_vm;

t_vm	*g_vm;

/*
**------Functions in parse_args_vm.c
*/

void			parse_args(char const **argv);
void			init_champs(char const **argv);
void			init_vm(char const **argv);

/*
**------Functions in utils_vm.c
*/

void			print_usage(void);
void			ft_error(char *s);



#endif
