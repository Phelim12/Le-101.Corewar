/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:55:56 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 17:23:15 by nbettach    ###    #+. /#+    ###.fr     */
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
#include <errno.h>
#include "op.h"
#include "../../Libft/Includes/libft.h"

#define DASH			'-'
#define QUOTE			'"'
#define SHARP			'#'
#define POINT			'.'
#define PERCENT			'%'
#define NEW_LINE		'\n'


#define HEADER_CHARS	"acemnot"
#define NUMBER_CHARS	"0123456789"
#define DIRECT_CHARS	"-0123456789"
#define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789:"
#define VALID_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789#%:.,-\""
#define ERROR_MSG_01	"Syntax error at token [TOKEN][001:001] END \"(null)\""

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

# define BUFF_ELEM				32
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

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

typedef enum		e_token
{
	COMMAND_COMMENT = 1,
	INDIRECT_LABEL,
	COMMAND_NAME,
	INSTRUCTION,
	INDIRECT,
	DIRECT,
	STRING,
	LABEL,
}					t_token;

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	char			prog_name[PROG_NAME_LENGTH + 1];
}					t_header;

typedef struct	s_op
{
	char			*name;
	char			nb_params;
	char			params[3];
	char			opcode;
	int				cycle;
	char			*desc;
	char			occode;
	char			not_identify;
}				t_op;

typedef struct	s_pos
{
	int				x;
	int				y;
}				t_pos;

typedef struct	s_label
{
	char			*name;
	struct s_cmd	*go_to;
	struct s_label	*prev;
	struct s_label	*next;
	struct s_label	*start;
}				t_label;

typedef struct	s_cmd
{
	struct s_cmd	*start;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*data;
	int				token;
	t_pos			pos;
}				t_cmd;

typedef struct	s_line
{
	t_cmd			*line;
	struct s_line	*next;
	struct s_line	*prev;
	struct s_line	*start;
}				t_line;

typedef struct	s_file
{
	t_header		header;
	t_line			*file;
}				t_file;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                fill_header.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*fill_prog_name(t_line *file, t_cmd *line);
char		*fill_comment(t_line *file, t_cmd *line);
t_header	fill_header(t_line *file);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                take_elem.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*realloc_str(char *str, int size);
char		*init_params_take_elem(char **str, int *var, char start);
char		take_elem(t_pos *position, char **str, char start, int fd);
void		refresh_pos_token(t_pos *position, char start, char buf, int option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 reader.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_line		*reader(t_line *result, t_line *previous, int fd);
int			find_buffer_elem(t_pos *position, char *buf, int ret, int fd);
void		add_elem(t_cmd **result, t_pos *position, char *buf, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               print_error.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_reader(t_line *result, t_pos position);
void		print_error_token(t_line *file, t_cmd *line, char *name);
void		print_error_size_header(t_line *file, char *cmd, int size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_asm.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_pos		init_pos(int y, int x);
void		free_file(t_line *file);
void		free_line(t_cmd *line);
void		print_line(t_cmd *pointer);
void		print_file(t_line *pointer);
void		ft_putnbr_pad3_fd(int nbr, int fd);
int			skip_comment(t_pos *position, char *buf, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  parser.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_label(t_line *file, t_label *lab);

#endif
