/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_asm.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/29 15:55:56 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 20:35:04 by nbettach    ###    #+. /#+    ###.fr     */
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

#define QUOTE			'"'
#define SHARP			'#'
#define POINT			'.'

#define STR_1			"\"\0"
#define STR_2			"\n\0"
#define STR_3			"\t \0"
#define STR_4			"\n\t :,\0"

#define SPACE_CHARS		" \t\v\f\r"
#define REGISTER_CHARS	"r0123456789"
#define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"


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

typedef struct	s_cmd
{
	char			*data;
	char			*name;
	char			*type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_cmd	*start;
	int				index;
}				t_cmd;

typedef struct	s_parser
{
	struct t_head	*head;
	struct t_cmd	*file;
}				t_parser;

t_cmd	*reader(int index, int fd);
char		**ft_strsplit_str(const char *src, char *str);

#endif
