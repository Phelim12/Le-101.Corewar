/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 23:06:58 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 23:06:58 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAIN_ASM_H
# define MAIN_ASM_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../../Libft/Includes/libft.h"
# include "op.h"

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
**┃                                 asm_tools.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_pos		init_pos(int y, int x);
char		*realloc_str(char *str, int size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               parser_header.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			token_header(int token);
void		parser_name(char *result, t_line *file);
void		parser_comment(char *result, t_line *file);
t_line		*delete_header(t_line *file, int size_header);
t_header	parser_header(t_line **file, int comment, int name);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                free_tools.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		free_line(t_cmd *line);
void		free_file(t_line *file);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   label.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_lab(t_label *lab);

int			check_double(t_label *lab);
int			check_label(t_line *file, t_label *lab);
void		print_label(t_line *file, t_label *lab);
int			check_label_next(char *str, t_label *lab, int in_direct);
int			check_double_next(t_label *lab, char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   label_create.c                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
int			add_label(t_label **result, t_cmd **line);
int			init_label(t_label **result, t_line **file, t_cmd **line);
int			init_label_next(t_line *tmpfile, t_label **result);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                print_error.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_token(t_line *file, t_cmd *cmd);
void		print_error_lexical(t_line *result, t_pos position);
void		print_error_size_header(t_line *file, char *cmd, int size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                print_tools.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_line(t_cmd *pointer);
void		print_file(t_line *pointer);
void		print_coord_token(int nbr, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                parser_asm.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			cmd_is_good(char *cmd);
t_line		*parser(t_line *result, int fd);
int			add_cmd(t_cmd **result, t_pos *pos, char *buf, int fd);
int			add_line(t_line **result, t_pos *pos, char *buf, int fd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               parser_tools.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			pass_comment(char *buf, int fd);
int			special_read(t_pos *pos, char *buf, int ret, int fd);
void		init_parser(t_line **result, t_pos *pos, char *buf, int *ret);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 take_elem.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			stop_elem(char *str, char start, char buf, int var);
char		parser_elem(t_pos *pos, char **str, char start, int fd);
char		*init_parse_elem(char **str, int *var, char start, char buf);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                token_tools.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*token_name(int token);
int			token_dispenser(char *cmd, char *buf, int string);

#endif
