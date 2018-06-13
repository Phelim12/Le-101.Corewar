/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 14:32:52 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 18:08:55 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	print_lab(t_label *lab)
{
	while (lab)
	{
		ft_printf("LABEL FINAL: %s - %s\n", lab->name, lab->go_to->data);
		lab = lab->next;
	}
}

int		ft_labelspec(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (str[0] == ':' && len > 1)
		return (1);
	else if (len > 1 && str[len - 1] == ':')
		return (2);
	else
		return (0);
}

void	add_label(t_label **result)
{
	t_label	*previous;

	previous = (*result) ? (*result) : NULL;
	(*result) = (*result) ? (*result)->next : *result;
	(*result) = ft_memalloc(sizeof(t_label));
	if (((*result)->prev = (previous) ? previous : NULL))
		previous->next = (*result);
	(*result)->start = (previous) ? previous->start : (*result);
}

void	init_label(t_label **result, t_line **file, t_cmd **line)
{
	(*result)->name = ft_strdup((*line)->data);
	(*result)->name[ft_strlen((*result)->name + 1)] = 0;
	if ((*line)->next)
		(*result)->go_to = (*line)->next;
	else if ((*file)->next)
		(*result)->go_to = (*file)->next->line;
	else
		ft_printf("Error\n");
}

int		check_label_next(char *str, t_label *lab)
{
	int		f;

	f = 0;
	while (lab)
	{
		if (!ft_strcmp(lab->name, str + 1))
			f++;
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
	if (!f)
		return (1);
	return (0);
}

int		check_label(t_line *file, t_label *lab)
{
	while (file)
	{
		while (file->line)
		{
			if (ft_labelspec(file->line->data) == 1)
			{
				printf("%s\n", file->line->data);
				if (check_label_next(file->line->data, lab))
					return (1);
			}
			file->line = (file->line->next) ? file->line->next : file->line->start;
			if (file->line == file->line->start)
				break;
		}
		file = (file->next) ? file->next : file->start;
		if (file == file->start)
			break;
	}
	return (0);
}

int		check_double_next(t_label *lab, char *str)
{
	int		err;
	t_label *tmplab;

	tmplab = lab;
	err = -1;
	while (lab)
	{
		if (!ft_strcmp(str, lab->name))
			err++;
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
	lab = tmplab;
	if (err)
		return (1);
	return (0);
}

int		check_double(t_label *lab)
{
	while (lab->next)
	{
		if (check_double_next(lab, lab->name))
			return (1);
		lab = (lab->next) ? lab->next : lab->start;
		if (lab == lab->start)
			break;
	}
	return (0);
}

void	print_label(t_line *file, t_label *lab)
{
	t_line	*tmp_file;
	int		i;

	while (file)
	{
		i = -1;
		while (file->line && ++i < 1)
		{
			if (ft_labelspec(file->line->data) == 2)
			{
				add_label(&lab);
				init_label(&lab, &file, &file->line);
			}
			file->line = (file->line->next) ?
				file->line->next : file->line->start;
		}
		file = (file->next) ? file->next : file->start;
		if (file == file->start)
			break;
	}
	print_lab(lab->start);
	printf("\ncheck_double\n");
	if (check_double(lab->start))
		ft_printf("Error\n");
	printf("\ncheck_label\n\n");
	if (check_label(file->start, lab->start))
		ft_printf("Error\n");
}
