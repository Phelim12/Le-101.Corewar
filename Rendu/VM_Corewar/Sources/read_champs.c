/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 14:10:23 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 16:28:54 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

unsigned int	BigToLittleEndian(unsigned int i)
{
	i = ((i >> 24) & 0xff) |
	((i << 8) & 0xff0000) |
	((i >> 8) & 0xff00) |
	((i << 24) & 0xff000000);
	return (i);
}

int		get_header(int i)
{
	int fd;
	char *s = NULL;
	t_header *header;

	header = malloc(sizeof(t_header));
	if ((fd = open(g_vm->champion[i]->filename, O_RDONLY, 555)) == -1)
		return (-1);
	if (read(fd, header, sizeof(t_header)) == -1)
		return (-1);
	g_vm->champion[i]->name = ft_strdup(header->prog_name);
	g_vm->champion[i]->comment = ft_strdup(header->comment);
	g_vm->champion[i]->prog_size = BigToLittleEndian(header->prog_size);
	// Ex : 0xA0b70708 =>  Big Endian : |A0|B7|07|08;  Little Endian : |08|07|B7|A0|;
	g_vm->champion[i]->magic = BigToLittleEndian(header->magic);
	free(header);
	return (fd);
}

int		get_instructions(int i, int fd)
{
	int j;
	int ret;

	j = -1;
	ret = 0;
	g_vm->champion[i]->instructions = malloc(g_vm->champion[i]->prog_size);
	while ((ret = read(fd, &g_vm->champion[i]->instructions[++j], 1)) > 0 )
		;
//		dprintf(1, "%02x|", g_vm->champion[i]->instructions[j]);
	dprintf(1, "\n-----------\ninstructions:%s\n", g_vm->champion[i]->instructions);
	if (ret >= 0)
		return (0);
	else
		return (-1);
}

int		get_champ(int i)
{
	int fd;

	if ((fd = get_header(i)) == -1)
		return (-1);
	if ((get_instructions(i, fd)) == -1)
		return (-1);
	return (0);
}
