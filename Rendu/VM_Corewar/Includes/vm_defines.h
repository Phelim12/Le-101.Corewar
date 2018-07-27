/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm_defines.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 20:19:01 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 20:19:01 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef VM_DEFINES_H
# define VM_DEFINES_H

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 TYPE SIZE                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define IND_SIZE		2
# define REG_SIZE		4
# define DIR_SIZE		REG_SIZE

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 TYPE CODE                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define T_REG			1
# define T_DIR			2
# define T_IND			4
# define T_LAB			8
# define REG_CODE		1
# define DIR_CODE		2
# define IND_CODE		3

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 REG LIMITS                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define MIN_REG		1
# define MAX_REG		16
# define REG_NUMBER		16

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            INSTRUCTIONS DEFINES                            ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define LIVE			1
# define LD				2
# define ST				3
# define ADD			4
# define SUB			5
# define AND			6
# define OR				7
# define XOR			8
# define ZJMP			9
# define LDI			10
# define STI			11
# define FORK			12
# define LLD			13
# define LLDI			14
# define LFORK			15
# define AFF			16

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                CODE DEFINES                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define PROC		(*proc)
# define USE1 		"Usage: ./corewar [-d N] [[-n number] champion1.cor] ...\n"
# define USE2 		"\t-d N\t: dump memory after nbr_cycles then exit\n"
# define USE3 		"\t-n number\t: set the number of the next player\n"

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 VM DEFINES                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

# define MAX_PLAYERS		4
# define MAX_CHECKS			10
# define NBR_LIVE			21
# define CYCLE_DELTA		50
# define CYCLE_TO_DIE		1536
# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define MEM_SIZE			(4*1024)
# define COREWAR_EXEC_MAGIC	0xea83f3
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)
# define IDX_MOD			(MEM_SIZE / 8)

#endif
