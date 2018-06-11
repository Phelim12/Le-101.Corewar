/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:55:56 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 19:41:54 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAIN_ASM
# define MAIN_ASM

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"
#include "../../Libft/Includes/libft.h"

#define DASH			'-'
#define QUOTE			'"'
#define SHARP			'#'
#define POINT			'.'
#define NEW_LINE		'\n'


#define HEADER_CHARS	"acemnot"
#define NUMBER_CHARS	"0123456789"
#define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
#define VALID_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789#%:.,-\n\""
#define ERROR_MSG_01	"Syntax error at token [TOKEN][001:001] END \"(null)\""


#define BUFF_ELEM	32

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃ Functions alloweds:                                                        ┃
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

typedef struct	s_pos
{
	int				x;
	int				y;
}				t_pos;

typedef struct	s_cmd
{
	char			*data;
	char			*name;
	char			*type;
	int				index;
	struct s_cmd	*start;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_pos	pos;
}				t_cmd;

typedef struct	s_parser
{
	struct t_head	*head;
	struct t_cmd	*file;
}				t_parser;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                take_elem.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char	*realloc_str(char *str, int size);
char	*init_params_take_elem(char **str, int *var, char start);
char	take_elem(t_pos *position, char **str, char start, int fd);
void	refresh_pos_token(t_pos *position, char start, char buf, int option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 reader.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_cmd	*reader(t_cmd *result, t_cmd *previous, int fd);
void	print_error_reader(t_cmd *result, t_pos position);
int		find_buffer_elem(t_pos *position, char *buf, int fd);
void	add_elem(t_cmd **result, t_pos *position, char *buf, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_asm.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_pos	init_pos(int y, int x);
void	free_list(t_cmd *list);
void	print_list(t_cmd *pointer);

#endif
