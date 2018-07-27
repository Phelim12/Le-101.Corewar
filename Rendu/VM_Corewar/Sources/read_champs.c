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

unsigned int	little_endian(unsigned int i)
{
	i = ((i >> 24) & 0xff) | ((i << 8) & 0xff0000) |
		((i >> 8) & 0xff00) | ((i << 24) & 0xff000000);
	return (i);
}

int				read_header(int i)
{
	t_header	*header;
	int			fd;

	if (!(header = malloc(sizeof(t_header))))
		return (-1);
	if ((fd = open(g_vm->champion[i]->filename, O_RDONLY)) == -1 ||
			read(fd, header, sizeof(t_header)) == -1)
		error_vm("open", i);
	if (!(g_vm->champion[i]->name = ft_strdup(header->prog_name)))
		return (-1);
	if (!(g_vm->champion[i]->comment = ft_strdup(header->comment)))
		return (-1);
	g_vm->champion[i]->magic = little_endian(header->magic);
	g_vm->champion[i]->prog_size = little_endian(header->prog_size);
	free(header);
	return (fd);
}

int				read_code(int i, int fd)
{
	int			size;
	int			ret;

	ret = 0;
	size = g_vm->champion[i]->prog_size;
	if (!(g_vm->champion[i]->instructions = malloc(size + 1)))
		return (-1);
	return (read(fd, g_vm->champion[i]->instructions, size));
}

int				read_champ(int i)
{
	int			fd;

	fd = read_header(i);
	if (fd == -1)
		return (-1);
	if ((read_code(i, fd)) == -1)
		return (-1);
	return (0);
}
