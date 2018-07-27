/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_structs.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 20:17:37 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 20:17:37 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VM_STRUCTS_H
# define VM_STRUCTS_H

typedef struct				s_op
{
	char			*name;
	char			nparams;
	char			params[4];
	char			opcode;
	int				cycles;
	char			*desc;
	char			info_params;
	char			size_dir;
}							t_op;

typedef struct				s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}							t_header;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃ typedef struct				s_process									   ┃
**┃ {																		   ┃
**┃ 	int					*reg;		  | reg for the mighty champion		   ┃
**┃ 	char				carry;		  | Dayum carry						   ┃
**┃ 	unsigned char		*params;	  | Current instruction saved		   ┃
**┃ 	char				ocp;		  | Current ocp						   ┃
**┃ 	int					cycle_delay;  | Cycles needed to exec instruct	   ┃
**┃ 	int					live;		  | Num o live since last cycle_to_die ┃
**┃ 	struct s_process	*next;		  | Next and older process			   ┃
**┃ }							t_process;									   ┃
**┃																			   ┃
**┃ Linked list ordered from the younger to the older, finaly linked to NULL,  ┃
**┃ in order to respect the ancestral rule which allows the youngest to begin  ┃
**┃ with hostilities.														   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct				s_process
{
	int					num;
	int					*reg;
	int					begin;
	char				carry;
	int					params[4][2];
	char				op;
	int					player;
	int					creation;
	int					cycle_delay;
	int					live;
	struct s_process	*next;
}							t_process;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃ typedef struct				s_champ										   ┃
**┃ {																		   ┃
**┃ 	unsigned int	magic;		   | Magic f**kin number				   ┃
**┃ 	unsigned int	prog_size;	   | Champion size						   ┃
**┃ 	char			*filename;	   | Filename							   ┃
**┃ 	int				live;		   | Obsolete ? Mb total lives for champion┃
**┃ 	char			*name;		   | Apocalyptic name of Hell			   ┃
**┃ 	char			*comment;	   | Funniest comment written by bonobos   ┃
**┃ 	int				num;		   | Number of player					   ┃
**┃ 	unsigned char	*instructions; | Finnest part of the champion		   ┃
**┃ }							t_champ;									   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct				s_champ
{
	unsigned int	magic;
	unsigned int	prog_size;
	int				live;
	char			*name;
	char			*comment;
	char			*filename;
	int				num;
	unsigned char	*instructions;
}							t_champ;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃ typedef struct				s_vm                                           ┃
**┃ {																		   ┃
**┃ 	int				cycle_to_die;  | Various limit of CYCLE_TO_DIE         ┃
**┃ 	unsigned int	cycle;		   | Total number of cycles passed         ┃
**┃ 	unsigned int	checks;		   | Num of cycle_to_die passed w/o changes┃
**┃ 	t_champ			**champion;	   | Tab of structs, with champs inside    ┃
**┃ 	t_process		*list_process; | Linked list of proc., younger to older┃
**┃ 	unsigned char	*map;		   | The ARENA of MEM_SIZE                 ┃
**┃ 	char			*p_map;		   | 'Filter map', for colors              ┃
**┃ 	int				dump;		   | Flag dump                             ┃
**┃ 	unsigned int	d_cycles;	   | Nombre de cycles avant le dump        ┃
**┃ 	unsigned int	nb_players;	   | Nombre de players					   ┃
**┃ }							t_vm;										   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

typedef struct				s_vm
{
	int				nb_proc;
	int				cycle_to_die;
	unsigned int	cycle;
	unsigned int	checks;
	t_champ			**champion;
	t_process		*list_process;
	int				nb_live;
	int				last_live;
	unsigned char	*map;
	char			*p_map;
	int				dump;
	int				v;
	int				d_size;
	unsigned int	d_cycles;
	unsigned int	nb_players;
}							t_vm;
t_vm						*g_vm;

#endif
