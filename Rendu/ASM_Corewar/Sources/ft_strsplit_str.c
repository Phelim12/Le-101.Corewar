/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit_str.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/06 12:50:29 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 12:50:29 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "main_asm.h"

static int	ft_count_words(const char *src, char *str)
{
	int nb_words;

	nb_words = 0;
	while (*src)
		if (ft_strchr(str, *src++))
			nb_words++;
	return (nb_words + 2);
}

static int	ft_lenchr(const char *src, char *str)
{
	int a;

	a = 0;
	while (!(ft_strchr(str, *src)) && src[a] != '\0')
		a++;
	return (a);
}

static char	*ft_fillstr(const char *src, char *str)
{
	char	*new_s;
	int		a;

	a = 0;
	new_s = ft_strnew(ft_lenchr(src, str));
	while (!(ft_strchr(str, *src)) && *src != '\0')
		new_s[a++] = *src++;
	new_s[a] = '\0';
	return (new_s);
}

char		**ft_strsplit_str(const char *src, char *str)
{
	char	**tab;
	int		a;

	a = 0;
	if (!src)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * ft_count_words(src, str));
	if (!tab)
		return (NULL);
	while (*src)
	{
		while (ft_strchr(str, *src))
			src++;
		if (*src != '\0')
			tab[a++] = ft_fillstr(src, str);
		while (!(ft_strchr(str, *src)) && *src != '\0')
			src++;
	}
	tab[a] = NULL;
	return (tab);
}
