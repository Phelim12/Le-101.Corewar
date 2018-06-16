/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/16 20:34:16 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/16 20:34:16 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_asm.h"

int		error_on_cmd(char *cmd, char buf)
{
	if (cmd[0] == CMD_CHAR &&
		ft_strcmp(cmd, CMD_NAME) && ft_strcmp(cmd, CMD_COMMENT))
		return (1);
	if ((ft_nbrchr(cmd, NEGATIVE_CHAR)) > 1)
		return (1);
	if (!(ft_strcmp(cmd, "%")))
		return (1);
	if (!(ft_strcmp(cmd, ":")))
		return (1);
	if (!(ft_strcmp(cmd, "-")))
		return (1);
	return (0);
}
