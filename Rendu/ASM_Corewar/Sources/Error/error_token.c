/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_token.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 20:05:59 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 20:05:59 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_coord_token(t_pos pos, int fd)
{
	if (!pos.x)
		pos.x++;
	if (pos.y < 100)
		ft_putchar_fd('0', fd);
	if (pos.y < 10)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(pos.y, fd);
	ft_putchar_fd(':', 2);
	if (pos.x < 100)
		ft_putchar_fd('0', fd);
	if (pos.x < 10)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(pos.x, fd);
}

void	print_error_msg(t_cmd *cmd, int msg_error)
{
	if (msg_error == SYNTAX_MSG)
		ft_putstr_fd(MSG_SYNTAX, 2);
	if (msg_error == DUP_LABEL_MSG)
		ft_putstr_fd(MSG_LABEL_1, 2);
	if (msg_error == NOT_EXIST_LABEL_MSG)
	{
		ft_putstr_fd(MSG_LABEL_2, 2);
		if (cmd->token == DIRECT_LABEL)
			ft_putstr_fd((cmd->data + 2), 2);
		if (cmd->token == INDIRECT_LABEL)
			ft_putstr_fd((cmd->data + 1), 2);
		ft_putstr_fd(MSG_LABEL_3, 2);
	}
	if (msg_error == INVALID_INSTRUCTION_MSG)
		ft_putstr_fd(MSG_INSTRUCTION, 2);
}

void	print_error_token(t_line *file, t_cmd *cmd, int msg_error)
{
	print_error_msg(cmd, msg_error);
	print_coord_token(cmd->pos, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(token_name(cmd->token), 2);
	ft_putchar_fd(' ', 2);
	if (cmd->token == STRING)
		ft_putchar_fd('"', 2);
	if (cmd->token != ENDLINE)
		ft_putchar_fd('"', 2);
	if (cmd->data[0] > 32)
		ft_putstr_fd(cmd->data, 2);
	if (cmd->token == END)
		ft_putstr_fd("(null)", 2);
	if (cmd->token != ENDLINE)
		ft_putchar_fd('"', 2);
	if (cmd->token == STRING)
		ft_putchar_fd('"', 2);
	ft_putchar_fd('\n', 2);
	free_file(file);
	exit(EXIT_FAILURE);
}

/*
P1 | live -1						P1 |	sti	r13, r16, r12		PC -> 3073		Cycle 1806
P6 | zjmp 502 OK					P2 |	live	-1		PC -> 42		Cycle 1806
P3 | sti r13 509 0					P7 |	zjmp	502		PC -> 2571		Cycle 1807
P1 | st r16 -300					P4 |	sti	r13, r16, r12		PC -> 3073		Cycle 1807
P8 | sti r3 28 0					P2 |	st	r16, -300		PC -> 47		Cycle 1811
P7 | sti r3 495 0					P8 |	sti	r3, r4, r5		PC -> 1675		Cycle 1812
P1 | st r2 -301						P6 |	sti	r3, r4, r5		PC -> 1675		Cycle 1812
P1 | st r2 -302						P2 |	st	r2, -301		PC -> 52		Cycle 1816
P4 | zjmp 19 OK						P2 |	st	r2, -302		PC -> 57		Cycle 1821
P2 | zjmp 500 OK					P3 |	zjmp	19		PC -> 1680		Cycle 1822
P3 | zjmp 500 OK					P1 |	zjmp	500		PC -> 3078		Cycle 1826
P5 | sti r13 511 0					P4 |	zjmp	500		PC -> 3078		Cycle 1827
P1 | sub r11 r12 r11				P5 |	sti	r13, r16, r12		PC -> 3073		Cycle 1831
P8 | zjmp 19 OK						P2 |	sub	r11, r12, r11		PC -> 62		Cycle 1831
P7 | zjmp 19 OK						P8 |	zjmp	19		PC -> 1680		Cycle 1832
P6 | sti r13 507 0					P7 |	sti	r13, r16, r12		PC -> 3073		Cycle 1832
P2 | xor 190056971 0 r9				P6 |	zjmp	19		PC -> 1680		Cycle 1832
P3 | xor 201916918 0 r9				P1 |	xor	r9, r12, r9		PC -> 3578		Cycle 1832
P4 | sti r3 24 0					P4 |	xor	r9, r12, r9		PC -> 3578		Cycle 1833
P5 | zjmp 500 OK					P3 |	sti	r3, r4, r5		PC -> 1699		Cycle 1847
P1 | zjmp 33 FAILED					P5 |	zjmp	500		PC -> 3078		Cycle 1851
P6 | zjmp 500 OK					P2 |	zjmp	33		PC -> 67		Cycle 1851
P1 | ld 0 r16						P7 |	zjmp	500		PC -> 3078		Cycle 1852
P8 | sti r3 28 0					P2 |	ld	%0, r16		PC -> 70		Cycle 1856
P7 | sti r3 495 0					P8 |	sti	r3, r4, r5		PC -> 1699		Cycle 1857
P5 | xor 190056971 0 r9				P6 |	sti	r3, r4, r5		PC -> 1699		Cycle 1857
P2 | sti r2 511 0					P5 |	xor	r9, r12, r9		PC -> 3578		Cycle 1857
P6 | xor 201916918 0 r9				P1 |	sti	r2, r15, r12		PC -> 3583		Cycle 1857
P3 | sti r2 2 0						P7 |	xor	r9, r12, r9		PC -> 3578		Cycle 1858
P4 | zjmp 19 OK						P4 |	sti	r2, r15, r12		PC -> 3583		Cycle 1858
P1 | zjmp -35 OK					P3 |	zjmp	19		PC -> 1704		Cycle 1867
P8 | zjmp 19 OK						P2 |	zjmp	-35		PC -> 77		Cycle 1876
P7 | zjmp 19 OK						P8 |	zjmp	19		PC -> 1704		Cycle 1877
P5 | sti r2 6 0						P6 |	zjmp	19		PC -> 1704		Cycle 1877
P2 | sti r5 511 0					P5 |	sti	r2, r15, r12		PC -> 3583		Cycle 1882
*/