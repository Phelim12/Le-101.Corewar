/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 14:10:23 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 16:41:24 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

unsigned int	BigToLittleEndian(unsigned int size)
{
	size = ((size >> 24) & 0xff) |
	((size << 8) & 0xff0000) |
	((size >> 8) & 0xff00) |
	((size << 24) & 0xff000000);
	return (size);
}

int		get_header(int i, char *path)
{
	int fd;
	t_header *header;

	header = malloc(sizeof(t_header));
	if (!(path = ft_strjoin("../", g_vm->champion[i]->filename)))
		return (-1);
	if ((fd = open(g_vm->champion[i]->filename, O_RDONLY, 0555)) == -1)
		return (-1);
	if ((fd = read(fd, header, sizeof(t_header))) == -1)
		return (-1);
	g_vm->champion[i]->name = ft_strdup(header->prog_name);
	g_vm->champion[i]->comment = ft_strdup(header->comment);
	g_vm->champion[i]->prog_size = header->prog_size;
	g_vm->champion[i]->prog_size = BigToLittleEndian(header->prog_size); //          Ex : 0xA0b70708 =>     Big Endian : |A0|B7|07|08;     Little Endian : |08|07|B7|A0|;
	g_vm->champion[i]->magic = BigToLittleEndian(header->magic);
	ft_strdel(&path);
	free(header);
	return (0);
}
