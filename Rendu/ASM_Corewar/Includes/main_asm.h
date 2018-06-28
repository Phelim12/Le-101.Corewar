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
	int				value;
	struct s_cmd	*adress;
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
	int				octet;
	int				info;
	t_pos			pos;
}				t_cmd;

typedef struct	s_line
{
	int				size;
	t_cmd			*line;
	t_label			*label;
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
**┃                              convert_binary.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int		code_params(int type);
int		type_params(int token);
int		size_params(t_op info, int type);
int		count_byte_instruction(t_line *file, t_cmd *cmds);
int		fill_binary_cmd(t_line *file, t_cmd *result, int *ptr);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   op.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_op		*get_op_tab(void);
t_op		instruction_exist(char *cmd);
int			has_arg(char args, int query);

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
void		free_label(t_label *lab);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                label_error.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		label_exist(t_line *file, t_label *lab);
void		check_duplicate_label(t_label *label, t_line *file);
void		label_exist_next(t_line *file, t_cmd *cmd, t_label *label);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               parser_label.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_label		*init_parser_label();
int 		init_label_value(t_line *file, t_cmd *line);
void		add_label(t_label **result, t_line *file, t_cmd *line);
void		parser_label(t_line *file);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                print_error.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_size_code(t_line *file);
void		print_error_malloc_fail(t_line *file);
void		print_error_msg(t_cmd *cmd, int msg_error);
void		print_error_lexical(t_line *result, t_pos position);
void		print_error_token(t_line *file, t_cmd *cmd, int msg_error);
void		print_error_size_header(t_line *file, char *cmd, int size);
void		print_error_params(t_line *file, t_cmd *params, int index, int type);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                print_label_error.c                         ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_malloc_fail(t_line *file);
void		print_error_nolabel(t_line *file, t_cmd *cmd);
void		print_error_label_repeat(t_line *file, t_cmd *cmd);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                print_tools.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_lab(t_label *lab);
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

int			pass_comment(t_cmd *cmds, char *buf, int fd);
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
