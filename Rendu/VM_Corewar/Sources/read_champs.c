/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_champs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/13 14:10:23 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/13 15:28:43 by jjanin-r    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

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
	ft_strdel(&path);
	free(header);
	return (0);
}
