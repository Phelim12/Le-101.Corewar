/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_args_vm.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dguelpa <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 12:50:12 by dguelpa      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 11:31:06 by dguelpa     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/main_vm.h"

static void	parse_n(char const **argv, unsigned int *i, unsigned int *k)
{
	if (argv[*i + 1] && ft_strisdigit(argv[*i + 1]) &&
			ft_atoi(argv[*i + 1]) >= 0)
		g_vm->champion[*k]->num = ft_atoi(argv[*i + 1]);
	else
		ft_error("Wrong parameter for -n option, require an int > 0\n", 0);
	if (argv[*i + 2] &&
			!ft_strcmp(".cor", &argv[*i + 2][ft_strlen(argv[*i + 2]) - 4]))
		g_vm->champion[*k]->filename = ft_strdup(argv[*i + 2]);
	else
		ft_error("After -n, no file detected, or wrong extension\n", 0);
	*i += 3;
	*k += 1;
}

static void	parse_dump(char const **argv, unsigned int *i)
{
	g_vm->dump = 1;
	if (argv[*i + 1] && ft_strisdigit(argv[*i + 1]) &&
			ft_atoi(argv[*i + 1]) >= 0)
		g_vm->d_cycles = ft_atoi(argv[*i + 1]);
	else
		ft_error("wrong parameter for -dump option\n", 0);
	*i += 2;
}

void		parse_args(char const **argv)
{
	unsigned int	i;
	unsigned int	k;

	i = 1;
	k = 0;
	while (argv[i])
	{
		if (!ft_strcmp("-dump", argv[i]))
			parse_dump(argv, &i);
		else if (!ft_strcmp("-n", argv[i]))
			parse_n(argv, &i, &k);
		else if (!ft_strcmp(".cor", &argv[i][ft_strlen(argv[i]) - 4]))
			g_vm->champion[k++]->filename = ft_strdup(argv[i++]);
		else
			ft_error("An error occured in the argument passed to corewar\n", 0);
	}
}
