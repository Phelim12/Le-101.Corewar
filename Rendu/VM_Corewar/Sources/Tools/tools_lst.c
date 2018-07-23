/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_lst.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 17:00:45 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 17:04:29 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../Includes/main_vm.h"

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

void		lstnew_vm_init(t_process *new, int *registers)
{
	new->live = 0;
	new->begin = registers[0];
	new->cycle_delay = 0;
	new->carry = 0;
	new->next = NULL;
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
		if (!(new->registers = malloc(REG_SIZE * REG_NUMBER)))
			return (NULL);
		ft_memcpy(new->registers, registers, reg_size);
	}
	while (i < 4)
	{
		new->fetchqueue[i][0] = 0;
		new->fetchqueue[i++][1] = -1;
	}
	lstnew_vm_init(new, registers);
	return (new);
}
