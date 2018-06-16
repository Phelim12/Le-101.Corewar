/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_asm.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/09 18:53:36 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 15:16:51 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"

t_pos	init_pos(int y, int x)
{
	t_pos	result;

	result.x = x;
	result.y = y;
	return (result);
}

void	free_line(t_cmd *line)
{
	t_cmd	*ptr;

	if (line)
		line = line->start;
	while (line)
	{
		ptr = line;
		free(line->data);
		line = line->next;
		free(ptr);
	}
}

void	free_file(t_line *file)
{
	t_line	*ptr;

	if (file)
		file = file->start;
	while (file)
	{
		ptr = file;
		free_line(file->line);
		file = file->next;
		free(ptr);
	}
}

void	print_line(t_cmd *pointer)
{
	while (pointer)
	{
		ft_printf("[%s] ", pointer->data);
		pointer = pointer->next;
	}
	ft_printf("\n");
}

void	print_file(t_line *pointer)
{
	while (pointer)
	{
		ft_printf("LINE = ");
		print_line(pointer->line);
		pointer = pointer->next;
	}
}

void	ft_putnbr_pad3_fd(int nbr, int fd)
{
	if (nbr < 10)
		ft_putstr_fd("00", fd);
	else if (nbr < 100)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(nbr, fd);
}

int		skip_comment(t_pos *position, char *buf, int fd)
{
	while ((read(fd, buf, 1)) > 0)
		if ((*buf) == LINE_CHAR)
			return (1);
	return (0);
}

int		ft_strstrchr(const char *str, const char *strchr)
{
	int var;

	var = -1;
	while (str[++var])
		if (!(ft_strchr(strchr, str[var])))
			return (0);
	return (1);
}

int		ft_nbrchr(const char *str, char chr)
{
	int result;
	int var;

	var = -1;
	result = 0;
	while (str[++var])
		if (str[var] == chr)
			result++;
	return (result);
}
