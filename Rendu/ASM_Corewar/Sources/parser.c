/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/11 14:32:52 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/11 19:41:51 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

int		ft_charinstr(char *s1, char *s2)
{
	int		i;
	int		j;
	int		f;

	i = -1;
	while (s2[++i] != '\0')
	{
		j = -1;
		f = 0;
		while (s1[++j] != '\0')
			if (s2[i] == s1[j])
				f = 1;
		if (f == 0)
			return (-1);
	}
	return (0);
}

void	**print_list(t_cmd *pointer)
{
	void	**tab_label;
	int		i;

	i = -1;
	tab_label = NULL;
	while (pointer->next != NULL)
	{
		if (!ft_strcmp(pointer->data, "\n") && !ft_charinstr(LABEL_CHARS, pointer->next->data) && !ft_strcmp(pointer->next->next->data, ":"))
		{
			tab_label[++i] = pointer->next;
			pointer->next->type = "label";
		}
		pointer = pointer->next;
	}
	return (tab_label);
}
