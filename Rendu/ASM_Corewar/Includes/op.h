/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 23:07:07 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 23:07:07 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define REG_SIZE				1
# define IND_SIZE				2
# define DIR_SIZE				4

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define NAME_LENGTH			128
# define COMMENT_LENGTH			2048

typedef char		t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

typedef enum		e_token
{
	END,
	LABEL,
	DIRECT,
	STRING,
	ENDLINE,
	INDIRECT,
	REGISTER,
	SEPARATOR,
	INSTRUCTION,
	DIRECT_LABEL,
	COMMAND_NAME,
	INDIRECT_LABEL,
	COMMAND_COMMENT,
}					t_token;

typedef enum		e_msg
{
	SYNTAX_MSG,
	DUP_LABEL_MSG,
	NOT_EXIST_LABEL_MSG,
	INVALID_INSTRUCTION_MSG,
}					t_msg;

typedef struct		s_header
{
	unsigned int	magic;
	unsigned int	prog_size;
	char			name[NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct	s_op
{
	char			*name;
	char			nparams;
	char			params[4];
	char			opcode;
	int				cycles;
	char			*desc;
	char			info_params;
	char			size_dir;
}				t_op;

#endif
