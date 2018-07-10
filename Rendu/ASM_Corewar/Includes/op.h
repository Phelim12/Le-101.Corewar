/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 14:52:36 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 14:52:36 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define REG_SIZE				1
# define IND_SIZE				2
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define MAX_PLAYERS			4
# define MAX_ARGS_NUMBER		4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define COMMENT_CHAR			'#'
# define SEPARATOR_CHAR			','

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define NBR_LIVE				21
# define MAX_CHECKS				10
# define CYCLE_DELTA			50
# define CYCLE_TO_DIE			1536

typedef char	t_arg_type;

# define BUFF_ELEM				32
# define NAME_LENGTH			(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			name[NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*name;
	char			nparams;
	char			params[4];
	char			opcode;
	int				cycles;
	char			*desc;
	char			info_params;
	char			size_dir;
}					t_op;

#endif
