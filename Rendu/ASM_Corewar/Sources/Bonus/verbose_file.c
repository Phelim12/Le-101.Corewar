/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_file.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/29 16:14:37 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/29 16:14:37 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

void	verbose_code(t_line *file, t_line *tmp)
{
	t_cmd	*ptr;

	tmp = file;
	while (tmp)
	{
		ptr = tmp->line->start;
		if (ptr->token != END && ptr->token != ENDLINE)
			ft_printf("\n\n%s|%d  [%d]|%s", ITLC, tmp->size, ptr->octet, C_END);
		while (ptr)
		{
			if (ptr->token == LABEL)
				ft_printf(" %s(%s)%s", LGRAY, ptr->data, C_END);
			if (ptr->token == INSTRUCTION)
			{
				ft_printf("\n%s%s%s %s->%s ", INST, ptr->data, 
					C_END, YELLOW, C_END);
				verbose_params(tmp, ptr);
			}
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

void	verbose_header(t_header header)
{
	char *ptr1;
	char *ptr2;

	ft_printf("\n---------------------\n");
	ft_printf("%sMagic number :%s 0x%s\n", DGRAY, C_END,
			ptr1 = ft_utoa_base(header.magic, "0123456789abcdef"));
	ft_printf("%sName         :%s \"%s\"\n", BRED, C_END, header.name);
	ft_printf("%sSize         :%s %d Bytes - 0x%s\n", DGRAY, C_END,
			header.prog_size,
			ptr2 = ft_utoa_base(header.prog_size, "0123456789abcdef"));
	ft_printf("%sComment      :%s \"%s\"", BRED, C_END, header.comment);
	ft_printf("\n---------------------\n\n");
	ft_memdel((void**)&ptr1);
	ft_memdel((void**)&ptr2);
}

void	verbose_file(t_file info)
{
	verbose_header(info.header);
	verbose_code(info.file, NULL);
	ft_printf("\n\n");
}
