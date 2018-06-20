/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 14:32:52 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 11:19:04 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_lab(t_label *lab)
{
	while (lab)
	{
		ft_printf("LABEL FINAL: %s - %s TOKEN: %s\n", lab->name, lab->go_to->data, token_name(lab->go_to->token));
		lab = lab->next;
	}
}

void	check_label_next(t_line *file, t_cmd *cmd, t_label *lab, int in_direct)
{
	int		f;

	f = 0;
	while (lab)
	{
		if ((in_direct == 1) && (!ft_strcmp(lab->name, cmd->data + 1)))
			f++;
		else if ((in_direct == 2) && (!ft_strcmp(lab->name, cmd->data + 2)))
			f++;
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
	if (!f)
		print_error_nolabel(file ,cmd, lab);
}

void	check_label(t_line *file, t_label *lab)
{
	while (file)
	{
		while (file->line)
		{
			if (file->line->token == INDIRECT_LABEL ||
					file->line->token == DIRECT_LABEL)
				check_label_next(file, file->line, lab,
					(file->line->token == (DIRECT_LABEL) ? 2 : 1));
			file->line = (file->line->next) ? file->line->next
			: file->line->start;
			if (file->line == file->line->start)
				break;
		}
		file = (file->next) ? file->next : file->start;
		if (file == file->start)
			break;
	}
}

void	check_double_next(t_label *lab, char *str, t_line *file)
{
	int		err;
	t_label *tmplab;

	tmplab = lab;
	err = -1;
	while (lab)
	{
		if (!ft_strcmp(str, lab->name))
			err++;
		if (err > 0)
			print_error_label_repeat(file, lab->place, lab);
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
	lab = tmplab;
}

void	check_double(t_label *lab, t_line *file)
{
	while (lab->next)
	{
		check_double_next(lab, lab->name, file);
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
}

t_label		*print_label(t_line *file, t_label *lab)
{
	int		i;

	while (file)
	{
		i = -1;
		while (file->line && ++i < 1)
		{
			if (file->line->token == LABEL)
			{
				add_label(&lab, &file->line, file);
				init_label(&lab, &file, &file->line);
			}
			file->line = (file->line->next) ?
				file->line->next : file->line->start;
		}
		file = (file->next) ? file->next : file->start;
		if (file == file->start)
			break;
	}
	//print_lab(lab->start);
	check_double(lab->start, file);
	check_label(file->start, lab->start);
	return (lab);
}
