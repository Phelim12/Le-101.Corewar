/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_define.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 19:09:19 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 19:09:19 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_DEFINE_H
# define ASM_DEFINE_H

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                CHAR DEFINES                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define CHAR_EOF			'\0'
# define CHAR_CMD			'.'
# define CHAR_LINE			'\n'
# define CHAR_LABEL			':'
# define CHAR_STRING		'"'
# define CHAR_DIRECT		'%'
# define CHAR_COMMENT		'#'
# define CHAR_NEGATIVE		'-'
# define CHAR_SEPARATOR		','

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               STRING DEFINES                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define CMD_NAME			".name"
# define CMD_COMMENT		".comment"
# define CHARS_CMD			"acemnot"
# define CHARS_NUMBER		"0123456789"
# define CHARS_DIRECT		"-0123456789"
# define CHARS_INSTRUCTION	"abcdefghijklmnopqrstuvwxyz_0123456789"
# define CHARS_LABEL		"abcdefghijklmnopqrstuvwxyz_0123456789:"
# define CHARS_VALID		"abcdefghijklmnopqrstuvwxyz_0123456789#%:.,-\""

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              MESSAGES DEFINES                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define MSG_DIR			"direct"
# define MSG_REG			"register"
# define MSG_IND			"indirect"
# define MSG_SIZE			"Code contains too many bytes (Max length "
# define MSG_SYNTAX			"Syntax error at token [TOKEN]["
# define MSG_LEXICAL		"Lexical error at ["
# define MSG_WRITING		"Writing output program to %s\n"
# define MSG_LABEL_1		"The label already exists at [TOKEN]["
# define MSG_LABEL_2		"No such label "
# define MSG_LABEL_3		" while attempting to dereference token [TOKEN]["
# define MSG_HEADER_1		"Champion "
# define MSG_HEADER_2		" too long (Max length "
# define MSG_PARAMS_1		"Invalid parameter "
# define MSG_PARAMS_2		" type "
# define MSG_PARAMS_3		" for instruction "
# define MSG_INSTRUCTION	"Invalid instruction at token [TOKEN]["

#endif