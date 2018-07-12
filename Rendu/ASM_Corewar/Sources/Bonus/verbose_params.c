/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_params.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 17:42:41 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 17:42:41 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	verbose_indirect(t_line *tmp, t_cmd *ptr)
{
	short	label_value;
	short	nb_ind;

	ft_printf("\n\t\t\t\t%s->%s %-20s -> [%s%s - %s0b11%s -",
			RED, C_END, ptr->data, ITLC, token_name(ptr->token), GREEN, C_END);
	if (ptr->token == INDIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data);
		verbose_binary_short(nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 1));
		nb_ind = label_value - (short)tmp->size;
		verbose_binary_short(nb_ind);
	}
}

void	verbose_direct_short(t_line *tmp, t_cmd *ptr)
{
	short	label_value;
	short	nb_ind;

	ft_printf("\n\t\t\t\t%s->%s %-20s -> [%s%s - %s0b10%s -",
			RED, C_END, ptr->data, ITLC, token_name(ptr->token), GREEN, C_END);
	if (ptr->token == DIRECT)
	{
		nb_ind = (short)ft_atoi(ptr->data + 1);
		verbose_binary_short(nb_ind);
	}
	else
	{
		label_value = (short)label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - (short)tmp->size;
		verbose_binary_short(nb_ind);
	}
}

void	verbose_direct_int(t_line *tmp, t_cmd *ptr)
{
	int	label_value;
	int	nb_ind;

	ft_printf("\n\t\t\t\t%s->%s %-20s -> [%s%s - %s0b10%s -",
			RED, C_END, ptr->data, ITLC, token_name(ptr->token), GREEN, C_END);
	if (ptr->token == DIRECT)
	{
		nb_ind = ft_atoi(ptr->data + 1);
		verbose_binary_int(nb_ind);
	}
	else
	{
		label_value = label_byte(tmp->label, (ptr->data + 2));
		nb_ind = label_value - tmp->size;
		verbose_binary_int(nb_ind);
	}
}

void	verbose_instructions(t_op *info, t_cmd *cmds)
{
	char	*ptr1;
	char	*ptr2;

	ft_printf("[0x%02s] ",
			ptr1 = ft_utoa_base(info->opcode, "0123456789abcdef"));
	ft_memdel((void**)&ptr1);
	if (info->info_params)
	{
		ft_printf("%s0b%08s%s - 0x%s", GREEN,
				ptr1 = ft_utoa_base(cmds->info, "01"),
				C_END,
				ptr2 = ft_utoa_base(cmds->info, "0123456789abcdef"));
		ft_memdel((void**)&ptr1);
		ft_memdel((void**)&ptr2);
	}
}

void	verbose_params(t_line *tmp, t_cmd *cmds)
{
	t_cmd	*ptr;
	t_op	info;

	ptr = cmds->next;
	info = instruction_exist(cmds->data);
	verbose_instructions(&info, cmds);
	while (ptr)
	{
		if (ptr->token == REGISTER)
			verbose_register(ptr);
		if (ptr->token == DIRECT_LABEL || ptr->token == DIRECT)
		{
			if (info.size_dir)
				verbose_direct_short(tmp, ptr);
			else
				verbose_direct_int(tmp, ptr);
		}
		if (ptr->token == INDIRECT_LABEL || ptr->token == INDIRECT)
			verbose_indirect(tmp, ptr);
		ptr = ptr->next;
	}
}
