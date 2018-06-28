/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_vm.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 16:14:53 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 13:29:32 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAIN_VM_H
# define MAIN_VM_H
# define USE1 "Usage: ./corewar [-d N] [[-n number] champion1.cor] ...\n"
# define USE2 "\t-d N\t: dump memory after nbr_cycles then exit\n"
# define USE3 "\t-n number\t: set the number of the next player\n"

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../../Libft/Includes/libft.h"
# include "../../Libft/Includes/libftprintf.h"

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

typedef struct				s_process
{
	int					*registers;
	unsigned char		*fetchqueue;
	int					cycle_delay;
	int					live;
	struct s_process	*next;
}							t_process;

typedef struct				s_champ
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			*filename;
	int				live;
	unsigned int	nb_process;
	char			*name;
	char			*comment;
	int				num;
	unsigned char	*instructions;

}							t_champ;

/*
**------Fetchqueue |cycle to exec|instruction sotcked in memory|
*/

typedef struct				s_vm
{
	int				cycle_to_die;
	unsigned int	cycle;
	unsigned int	checks;
	t_champ			**champion;
	t_process		*list_process;
	unsigned char	*map;
	char			*p_map;
	int				dump;
	unsigned int	d_cycles;
	unsigned int	nb_players;
}							t_vm;

t_vm						*g_vm;

/*
**------Functions in parse_args_vm.c
*/

void						parse_args(char const **argv);
void						init_champs(char const **argv);
void						init_vm(char const **argv);

/*
**------Fuctions in read_champs.c
*/

int							get_champ(int i);
int							get_header(int i);
int							get_instructions(int i, int fd);

/*
**------Functions in utils_vm.c
*/

int							process_remove_if_live(t_process **begin_list,
							int lives);
void						print_usage(void);
int							error_vm(char *s, int c);
int							check_data(void);

/*
**------Functions in rabbit_run.c
*/

int							cycling(void);

/*
**------Functions in lst_vm.c
*/

void						lstiter_vm(t_process *lst,
							void (*f)(t_process *elem));
void						lstadd_vm(t_process **alst, t_process *mew);
t_process					*lstnew_vm(int *registers,
							unsigned char *fetchqueue, int reg_size,
							int fetch_size);


/*
**------Functions in dump.c
*/

int							ft_dump(void);
int							print_color(int i, int *p);
/*
**----------------OP_H---------------
*/

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits.
*/

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

typedef char				t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct				s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}							t_header;
#endif
