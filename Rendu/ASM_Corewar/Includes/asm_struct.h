/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_struct.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 19:07:39 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 19:07:39 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_STRUCT_H
# define ASM_STRUCT_H

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

#endif
