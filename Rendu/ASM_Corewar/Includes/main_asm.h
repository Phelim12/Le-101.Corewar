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
#include "../../Libft/Includes/libft.h"

#define GOOD_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
#define NOT_GOOD_CHARS	""

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
	char			*name;
	char			*type;
	struct s_cmd	*next;
	int				index;
}				t_cmd;

typedef struct	s_line
{
	struct t_cmd	*cmds;
	struct s_line	*next;
	int				index;
}				t_line;

typedef struct	s_parser
{
	struct t_line	*file;
}				t_parser;

t_parser	*reader(const char *name);
char		**ft_strsplit_str(const char *src, char *str);

#endif
