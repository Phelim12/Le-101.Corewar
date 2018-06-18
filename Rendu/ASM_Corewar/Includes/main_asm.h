/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:55:56 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 11:19:01 by nbettach    ###    #+. /#+    ###.fr     */
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

/*
**	CHAR DEFINE
*/

# define EOF_CHAR				'\0'

# define CMD_CHAR				'.'
# define LINE_CHAR				'\n'
# define LABEL_CHAR				':'
# define STRING_CHAR			'"'
# define DIRECT_CHAR			'%'
# define COMMENT_CHAR			'#'
# define NEGATIVE_CHAR			'-'
# define SEPARATOR_CHAR			','

/*
**	STRING DEFINE
*/

# define CMD_NAME				".name"
# define CMD_CHARS				"acemnot"
# define CMD_COMMENT			".comment"
# define NUMBER_CHARS			"0123456789"
# define DIRECT_CHARS			"-0123456789"
# define INSTRUCTION_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789:"
# define VALID_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789#%:.,-\""

/*
**	INTEGER DEFINE
*/

# define BUFF_ELEM				32
# define NAME_LENGTH			128
# define COMMENT_LENGTH			2048
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

void		fill_name(char *result, t_line *file);
void		fill_comment(char *result, t_line *file);
t_header	fill_header(t_line **file, int comment, int name);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                take_elem.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*realloc_str(char *str, int size);
char		*init_take_elem(char **str, int *var, char start, char buf);
char		take_elem(t_pos *position, char **str, char start, int fd);
void		refresh_pos_token(t_pos *position, char start, char buf, int option);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 reader.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_line		*reader(t_line *result, int fd);
void		add_elem(t_cmd **result, t_pos *position, char *buf, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               print_error.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_lexical(t_line *result, t_pos position);
void		print_error_size_header(t_line *file, char *cmd, int size);
void		print_error_token(t_line *file, t_cmd *cmd);


/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_reader.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int		pass_comment(t_pos *pos, char *buf, int fd);
int		special_read(t_pos *pos, char *buf, int ret, int fd);
void	init_reader(t_line **result, t_pos *pos, char *buf, int *ret);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_asm.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*token_name(int token);
t_pos		init_pos(int y, int x);
void		free_file(t_line *file);
void		free_line(t_cmd *line);
void		print_line(t_cmd *pointer);
void		print_file(t_line *pointer);
void		ft_putnbr_p3_fd(int nbr, int fd);
int			token_dispenser(char *cmd, char buf);
char		*token_name(int token);
void		print_coord_token(int nbr, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  label.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			error_on_cmd(char *cmd, char buf);
void		print_label(t_line *file, t_label *lab);

#endif
