/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   label_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/23 17:12:02 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/23 17:12:02 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		label_byte(t_label *label, char *label_name)
{
	t_label *tmp;

	tmp = label;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, label_name)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	check_duplicate_label(t_label *label, t_line *file)
{
	t_label *ptr_1;
	t_label *ptr_2;

	ptr_1 = label;
	while (ptr_1)
	{
		ptr_2 = ptr_1->next;
		while (ptr_2)
		{
			if (!(ft_strcmp(ptr_1->name, ptr_2->name)))
				print_error_token(file, ptr_2->adress, DUP_LABEL_MSG);
			ptr_2 = ptr_2->next;
		}
		ptr_1 = ptr_1->next;
	}
}

void	label_exist_next(t_line *file, t_cmd *cmd, t_label *label)
{
	t_label	*ptr;
	int		exist;
	int		dir;

	exist = 0;
	ptr = label;
	dir = (cmd->token == DIRECT_LABEL) ? 1 : 0;
	while (ptr)
	{
		if (dir && !(ft_strcmp(ptr->name, cmd->data + 2)))
			exist++;
		if (!dir && !(ft_strcmp(ptr->name, cmd->data + 1)))
			exist++;
		ptr = ptr->next;
	}
	if (!exist)
		print_error_token(file, cmd, NOT_EXIST_LABEL_MSG);
}

void	label_exist(t_line *file, t_label *lab)
{
	t_line	*tmp;
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line;
		while (ptr)
		{
			if ((ptr->token == DIRECT_LABEL) ||
				(ptr->token == INDIRECT_LABEL))
				label_exist_next(tmp, ptr, lab);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}
