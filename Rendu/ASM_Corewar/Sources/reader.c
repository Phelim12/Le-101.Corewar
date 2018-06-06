/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reader.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nbettach <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 18:52:58 by nbettach     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 20:35:08 by nbettach    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"


t_line		*parse_file(char **cmd)
{
	t_line	*result;
	int		var;

	var = -1;
	result = (t_line*)ft_memalloc(sizeof(t_line));
	while (cmd[++var])
	{
		if (cmd[var][0] == '#')
			break ;
		if (ft_strchr(cmd[var], ""))
	}

}

t_parser	reader(const char *name)
{
	t_parser	result;
	char		*line;
	char		**cmd;
	int			var;
	int			fd;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		cmd = ft_strsplit_str(line, " \t");
		result.file = parse_file(cmd);

		var = -1
		while (cmd[++var])
		{
			printf("[%s] ", cmd[var]);
		}
		printf("\n");
	}
	return (result);
}


