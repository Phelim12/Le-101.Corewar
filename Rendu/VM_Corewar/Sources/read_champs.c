/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 14:10:23 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 01:14:59 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

unsigned int	big_to_little_endian(unsigned int i)
{
	i = ((i >> 24) & 0xff) |
	((i << 8) & 0xff0000) |
	((i >> 8) & 0xff00) |
	((i << 24) & 0xff000000);
	return (i);
}

int				get_header(int i)
{
	int			fd;
	t_header	*header;

	if (!(header = malloc(sizeof(t_header))))
		return (-1);
	if ((fd = open(g_vm->champion[i]->filename, O_RDONLY, 555)) == -1 ||
			read(fd, header, sizeof(t_header)) == -1)
		return (error_vm("open", i));
	if (!(g_vm->champion[i]->name = ft_strdup(header->prog_name)))
		return (-1);
	if (!(g_vm->champion[i]->comment = ft_strdup(header->comment)))
		return (-1);
	g_vm->champion[i]->prog_size = big_to_little_endian(header->prog_size);
	g_vm->champion[i]->magic = big_to_little_endian(header->magic);
	free(header);
	return (fd);
}

int				get_instructions(int i, int fd)
{
	int			j;
	int			ret;

	j = -1;
	ret = 0;
	if (!(g_vm->champion[i]->instructions =
				malloc(g_vm->champion[i]->prog_size)))
		return (-1);
	while ((ret = read(fd, &g_vm->champion[i]->instructions[++j], 1)) > 0)
		;
	if (ret >= 0)
		return (0);
	else
		return (-1);
}

int				get_champ(int i)
{
	int			fd;

	if ((fd = get_header(i)) == -1)
		return (-1);
	if ((get_instructions(i, fd)) == -1)
		return (-1);
	return (0);
}
