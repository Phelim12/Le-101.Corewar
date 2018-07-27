/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_functions.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 20:15:08 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 20:15:08 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VM_FUNCTIONS_H
# define VM_FUNCTIONS_H

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                                  COMMANDS                                  ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

void			ft_or(t_process **proc);
void			ft_st(t_process **proc);
void			ft_ld(t_process **proc);
void			ft_add(t_process **proc);
void			ft_aff(t_process **proc);
void			ft_and(t_process **proc);
void			ft_ldi(t_process **proc);
void			ft_lld(t_process **proc);
void			or_reg(t_process **proc);
void			or_dir(t_process **proc);
void			or_ind(t_process **proc);
void			ft_sti(t_process **proc);
void			ft_sub(t_process **proc);
void			ft_xor(t_process **proc);
void			and_reg(t_process **proc);
void			and_dir(t_process **proc);
void			and_ind(t_process **proc);
void			ft_live(t_process **proc);
void			ft_lldi(t_process **proc);
void			xor_reg(t_process **proc);
void			xor_dir(t_process **proc);
void			ft_zjmp(t_process **proc);
void			xor_ind(t_process **proc);
void			ft_fork(t_process **proc, t_process **begin);
void			ft_lfork(t_process **proc, t_process **begin);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                                   TOOLS                                    ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_error.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			print_usage(void);
void			print_error_read(int var);
void			print_error_size(int var);
void			error_vm(char *str, int var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                tools_free.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				free_all(void);
void			free_champs(void);
void			free_process(t_process *list);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            tools_instructions.c                            ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

unsigned char	*itoo(int nb);
int				read_map(int index);
int				check_reg(t_process *proc);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_lst.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_process		*lstnew_vm(int *reg, int reg_size);
void			lstnew_vm_init(t_process **new, int *reg);
void			lstadd_vm(t_process **alst, t_process *new);
void			lstiter_vm(t_process *lst, void (*f)(t_process *elem));

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_op.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_op			*get_op_tab(void);
t_op			get_opcode(char op_code);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_ocp.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				check_ocp(int op, int cursor);
int				check_ocp_two(int op, int cursor);
int				check_ocp_one(int op, int cursor);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools_vm.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				check_data(void);
void			introduction(void);
void			norme_remove(t_process **list);
void			print(int player, int index, int value);
void			process_remove_if_live(t_process **begin_list);

/*
**╔════════════════════════════════════════════════════════════════════════════╗
**║                                    EXEC                                    ║
**╚════════════════════════════════════════════════════════════════════════════╝
*/

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   cycle.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				cycling(void);
int				check_players_process(void);
int				check_destruction_process(int cycles_passed);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   dump.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				ft_dump(void);
int				print_color(int i, int *p, int pc);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   exec.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			exec_1(t_process **proc);
void			exec(t_process **proc, t_process **begin);
void			exec_2(t_process **proc, t_process **begin);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   init.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				init_map(void);
void			init_vm(char const **argv);
int				init_process(unsigned int a);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                init_champs.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			sort_champ_tab(void);
void			init_champ_num(void);
void			init_champs(char const **argv);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   move.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				valid_ocp(int cursor, t_op instruction, t_process **proc);
int				pass_params(int cursor, t_op instruction, t_process **proc);
int				read_params(int cursor, t_op instruction, t_process **proc);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  parser.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			parse_args(char const **argv);
void			parse_v(char const **argv, unsigned int *i);
void			parse_s(char const **argv, unsigned int *i);
void			parse_dump(char const **argv, unsigned int *i);
void			parse_n(char const **argv, unsigned int *i, unsigned int *k);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 process.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			process(void);
void			read_opcode(t_process **proc);
void			launch(t_process **proc, t_process **begin);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   read.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				read_reg(int cursor);
int				read_ind(int cursor);
void			read_instruction(t_process **proc);
int				read_dir(int cursor, t_op instruction);
int				read_ocp(int cursor, t_op instruction, t_process **proc);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               read_champs.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				read_champ(int i);
int				read_header(int i);
void			check_header(int i);
int				read_code(int i, int fd);
unsigned int	little_endian(unsigned int i);

#endif
