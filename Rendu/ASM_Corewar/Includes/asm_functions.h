/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_functions.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 19:13:33 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 19:13:33 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_FUNCTIONS_H
# define ASM_FUNCTIONS_H

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║              █████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗                   ║
**║             ██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝                   ║
**║             ██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗                   ║
**║             ██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║                   ║
**║             ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║                   ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                verbose_file.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		verbose_file(t_file info);
void		verbose_header(t_header header);
int			check_verbose(char const *argv[]);
void		verbose_code(t_line *file, t_line *tmp);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                verbose_params.c                            ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		verbose_params(t_line *tmp, t_cmd *cmds);
void		verbose_indirect(t_line *tmp, t_cmd *ptr);
void		verbose_direct_int(t_line *tmp, t_cmd *ptr);
void		verbose_instructions(t_op *info, t_cmd *cmds);
void		verbose_direct_short(t_line *tmp, t_cmd *ptr);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                 ███████┓██████┓ ██████┓  ██████┓ ██████┓                   ║
**║                 ██┏━━━━┛██┏━━██┓██┏━━██┓██┏━━━██┓██┏━━██┓                  ║
**║                 █████┓  ██████┏┛██████┏┛██┃   ██┃██████┏┛                  ║
**║                 ██┏━━┛  ██┏━━██┓██┏━━██┓██┃   ██┃██┏━━██┓                  ║
**║                 ███████┓██┃  ██┃██┃  ██┃┗██████┏┛██┃  ██┃                  ║
**║                 ┗━━━━━━┛┗━┛  ┗━┛┗━┛  ┗━┛ ┗━━━━━┛ ┗━┛  ┗━┛                  ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                error_asm.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_error_size_code(t_line *file);
void		print_error_lexical(t_line *result, t_pos position);
void		print_error_size_header(t_line *file, char *cmd, int size);
void		print_error_params(t_line *file, t_cmd *params, int nb, int type);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                error_file.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		file_not_exist(char *name);
void		cant_create_file(char *name_exec, t_file info);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               error_token.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		print_coord_token(t_pos pos, int fd);
void		print_error_msg(t_cmd *cmd, int msg_error);
void		print_error_token(t_line *file, t_cmd *cmd, int msg_error);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║              ██████┓  █████┓ ██████┓ ███████┓███████┓██████┓               ║
**║              ██┏━━██┓██┏━━██┓██┏━━██┓██┏━━━━┛██┏━━━━┛██┏━━██┓              ║
**║              ██████┏┛███████┃██████┏┛███████┓█████┓  ██████┏┛              ║
**║              ██┏━━━┛ ██┏━━██┃██┏━━██┓┗━━━━██┃██┏━━┛  ██┏━━██┓              ║
**║              ██┃     ██┃  ██┃██┃  ██┃███████┃███████┓██┃  ██┃              ║
**║              ┗━┛     ┗━┛  ┗━┛┗━┛  ┗━┛┗━━━━━━┛┗━━━━━━┛┗━┛  ┗━┛              ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

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
**┃                               parser_code.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		parser_code(t_line *file);
int			parser_instruction(t_line *file, t_cmd *cmds);
int			stop_params(t_line *file, t_cmd *result, t_op info);
int			parser_params(t_line *file, t_cmd *cmds, int *info_params);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               parser_elem.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			stop_elem(char *str, char start, char buf, int var);
char		parser_elem(t_pos *pos, char **str, char start, int fd);
char		*init_parser_elem(char **str, int *var, char start, char buf);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              parser_header.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			token_header(int token);
void		parser_name(char *result, t_line *file);
void		parser_comment(char *result, t_line *file);
t_line		*delete_header(t_line *file, int size_header);
t_header	parser_header(t_line **file, int comment, int name);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               parser_label.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_label		*init_parser_label(void);
void		parser_label(t_line *file);
int			init_label_value(t_line *file, t_cmd *line);
void		add_label(t_label **result, t_line *file, t_cmd *line);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                ████████┓ ██████┓  ██████┓ ██┓     ███████┓                 ║
**║                ┗━━██┏━━┛██┏━━━██┓██┏━━━██┓██┃     ██┏━━━━┛                 ║
**║                   ██┃   ██┃   ██┃██┃   ██┃██┃     ███████┓                 ║
**║                   ██┃   ██┃   ██┃██┃   ██┃██┃     ┗━━━━██┃                 ║
**║                   ██┃   ┗██████┏┛┗██████┏┛███████┓███████┃                 ║
**║                   ┗━┛    ┗━━━━━┛  ┗━━━━━┛ ┗━━━━━━┛┗━━━━━━┛                 ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_byte.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			code_params(int type);
int			type_params(int token);
int			size_params(t_op info, int type);
int			byte_info_params(t_line *file, t_cmd *cmd, t_op info, int type);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_free.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		free_line(t_cmd *line);
void		free_file(t_line *file);
void		free_label(t_label *lab);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_label.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		label_exist(t_line *file, t_label *lab);
int			label_byte(t_label *label, char *label_name);
void		check_duplicate_label(t_label *label, t_line *file);
void		label_exist_next(t_line *file, t_cmd *cmd, t_label *label);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_op.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_op		*get_op_tab(void);
t_op		instruction_exist(char *cmd);
int			has_arg(char args, int query);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_parser.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_pos		init_pos(int y, int x);
char		*realloc_str(char *str, int size);
int			pass_comment(t_cmd *cmds, char *buf, int fd);
int			special_read(t_pos *pos, char *buf, int ret, int fd);
void		init_parser(t_line **ptr, t_pos *pos, char *buf, int *ret);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_token.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char		*token_name(int token);
int			token_dispenser(char *cmd, char *buf, int string);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_verbose.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		verbose_register(t_cmd *ptr);
void		verbose_binary_int(int nb);
void		verbose_binary_short(short nb);
void		verbose_convert_short(unsigned char **ptr, int n);
void		verbose_convert_integer(unsigned char **ptr, int n);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tools_write.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		write_binary_int(int fd, int nb);
void		write_binary_short(int fd, short nb);
void		convert_short(unsigned char **ptr, int n);
void		convert_integer(unsigned char **ptr, int n);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                   ██┓    ██┓██████┓ ██┓████████┓███████┓                   ║
**║                   ██┃    ██┃██┏━━██┓██┃┗━━██┏━━┛██┏━━━━┛                   ║
**║                   ██┃ █┓ ██┃██████┏┛██┃   ██┃   █████┓                     ║
**║                   ██┃███┓██┃██┏━━██┓██┃   ██┃   ██┏━━┛                     ║
**║                   ┗███┏███┏┛██┃  ██┃██┃   ██┃   ███████┓                   ║
**║                    ┗━━┛┗━━┛ ┗━┛  ┗━┛┗━┛   ┗━┛   ┗━━━━━━┛                   ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                write_file.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		write_code(t_line *file, int fd);
char		*name_exec_file(const char *name);
void		write_header(t_header header, int fd);
void		write_file(t_file info, char *name);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               write_params.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void		write_register(t_cmd *ptr, int fd);
void		write_params(t_line *tmp, t_cmd *cmds, int fd);
void		write_indirect(t_line *tmp, t_cmd *ptr, int fd);
void		write_direct_int(t_line *tmp, t_cmd *ptr, int fd);
void		write_direct_short(t_line *tmp, t_cmd *ptr, int fd);

#endif
