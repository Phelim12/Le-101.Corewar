/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jjanin-r <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/27 18:24:43 by jjanin-r     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/27 18:24:59 by jjanin-r    ###    #+. /#+    ###.fr     */
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
		error_vm("Wrong parameter for -n option, require an int > 0\n", 0);
	if (argv[*i + 2] &&
			!ft_strcmp(".cor", &argv[*i + 2][ft_strlen(argv[*i + 2]) - 4]))
		g_vm->champion[*k]->filename = ft_strdup(argv[*i + 2]);
	else
		error_vm("After -n, no file detected, or wrong extension\n", 0);
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
		error_vm("wrong parameter for -d option\n", 0);
	*i += 2;
}

static void	parse_v(char const **argv, unsigned int *i)
{
	int		verbose;

	if (argv[*i + 1] && ft_strisdigit(argv[*i + 1]) &&
			ft_atoi(argv[*i + 1]) >= 0)
	{
		verbose = ft_atoi(argv[*i + 1]);
		if (verbose < 1 || verbose > 4)
			error_vm("Please enter a valid verbose mode (1 - 4)\n", 0);
		else
			g_vm->v = verbose;
	}
	else
		error_vm("wrong parameter for -v option\n", 0);
	*i += 2;
}

static void	parse_s(char const **argv, unsigned int *i)
{
	int		size;

	if (argv[*i + 1] && ft_strisdigit(argv[*i + 1]) &&
			ft_atoi(argv[*i + 1]) >= 0)
	{
		size = ft_atoi(argv[*i + 1]);
		if (size != 32 && size != 64)
			error_vm("Please enter a valid dump size (32 | 64)\n", 0);
		else
			g_vm->d_size = size;
	}
	else
		error_vm("wrong parameter for -s option\n", 0);
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
		if (!ft_strcmp("-d", argv[i]))
			parse_dump(argv, &i);
		else if (!ft_strcmp("-n", argv[i]))
			parse_n(argv, &i, &k);
		else if (!ft_strcmp(".cor", &argv[i][ft_strlen(argv[i]) - 4]))
			g_vm->champion[k++]->filename = ft_strdup(argv[i++]);
		else if (!ft_strcmp("-v", argv[i]))
			parse_v(argv, &i);
		else if (!ft_strcmp("-s", argv[i]))
			parse_s(argv, &i);
		else
			error_vm("An error occured in the argument passed to Corewar\n",
					0);
	}
}
