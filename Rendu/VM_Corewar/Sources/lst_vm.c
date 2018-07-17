/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_vm.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 12:22:43 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 15:57:36 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_vm.h"

void		lstadd_vm(t_process **alst, t_process *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

void		lstiter_vm(t_process *lst, void (*f)(t_process *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}

t_process	*lstnew_vm(int *registers, int reg_size)
{
	t_process	*new;
	int			i;

	i = 0;
	new = (t_process*)malloc(sizeof(t_process));
	if (!new)
		return (NULL);
	if (!registers)
		new->registers = NULL;
	else
	{
		if (!(new->registers = malloc(reg_size)))
			return (NULL);
		ft_memcpy(new->registers, registers, reg_size);
	}
	while (i < 4)
	{
		new->fetchqueue[i][0] = 0;
		new->fetchqueue[i++][1] = -1;
	}
	new->live = 0;
	new->cycle_delay = 0;
	new->carry = 0;
	new->next = NULL;
	return (new);
}
