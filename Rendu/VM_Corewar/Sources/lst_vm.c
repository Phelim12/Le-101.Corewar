/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_vm.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 12:22:43 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:48:41 by jjanin-r    ###    #+. /#+    ###.fr     */
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

t_process	*lstnew_vm(int *registers, t_op *fetchqueue, int reg_size,
		int fetch_size)
{
	t_process *new;

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
	if (!fetchqueue)
		new->fetchqueue = NULL;
	else
	{
		if (!(new->fetchqueue = malloc(fetch_size)))
			return (NULL);
		ft_memcpy(new->fetchqueue, fetchqueue, fetch_size);
	}
	new->live = 0;
	new->cycle_delay = 0;
	new->next = NULL;
	return (new);
}
