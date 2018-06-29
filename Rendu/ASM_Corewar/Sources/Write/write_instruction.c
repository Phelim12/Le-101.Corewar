/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_instruction.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:13:45 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 16:13:45 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	write_register(t_cmd *ptr, int fd)
{
	char	nb_reg;

	nb_reg = (char)ft_atoi(ptr->data + 1);
	write(fd, &(nb_reg), 1);
}

void	write_indirect(t_line *tmp, t_cmd *ptr, int fd)
{
	short	label_value;
	short	nb_ind;

	if (ptr->token == INDIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data);
		write_binary_short(fd, nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 1));
		nb_ind = label_value - (short)tmp->size;
		write_binary_short(fd, nb_ind);
	}
}

void	write_direct_short(t_line *tmp, t_cmd *ptr, int fd)
{
	short	label_value;
	short	nb_ind;

	if (ptr->token == DIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data + 1);
		write_binary_short(fd, nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - (short)tmp->size;
		write_binary_short(fd, nb_ind);
	}
}

void	write_direct_int(t_line *tmp, t_cmd *ptr, int fd)
{
	int	label_value;
	int	nb_ind;

	if (ptr->token == DIRECT)
	{
		nb_ind = ft_atoi(ptr->data + 1);
		write_binary_int(fd, nb_ind);
	}
	else
	{
		label_value = label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - tmp->size;
		write_binary_short(fd, nb_ind);
	}
}

void	write_instruction(t_line *tmp, t_cmd *cmds, int fd)
{
	t_cmd	*ptr;
	t_op	info;

	ptr = cmds->next;
	info = instruction_exist(cmds->data);
	write(fd, &(info.opcode), 1);
	if (info.info_params)
		write(fd, &(cmds->info), 1);
	while (ptr)
	{
		if (ptr->token == REGISTER)
			write_register(ptr, fd);
		if (ptr->token == DIRECT_LABEL || ptr->token == DIRECT)
		{
			if (info.size_dir)
				write_direct_short(tmp, ptr, fd);
			else
				write_direct_int(tmp, ptr, fd);
		}
		if (ptr->token == INDIRECT_LABEL || ptr->token == INDIRECT)
			write_indirect(tmp, ptr, fd);
		ptr = ptr->next;
	}
}