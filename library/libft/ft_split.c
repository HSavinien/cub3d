/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:54:11 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/05 01:17:16 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function that give the number of substring in the original string to split
static int	ft_count_str(char const *s, char c)
{
	int	i;
	int	nb_str;

	if (ft_strlen(s) == 0)
		return (0);
	i = 1;
	nb_str = 1;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			nb_str ++;
		i ++;
	}
	if (s[i - 1] == c)
		nb_str --;
	return (nb_str);
}

// function that give a pointer one the first char of the num^th substr of s.
static int	ft_find_substr(char const *s, char sep, int num)
{
	int		i;
	int		curent_str;

	if (num > ft_count_str(s, sep))
		return (-1);
	i = 0;
	curent_str = 1;
	while (curent_str < num + 1)
	{
		if (s[i] == sep && s[i - 1] != sep && i != 0)
			curent_str ++;
		i ++;
	}
	while (s[i] == sep)
		i ++;
	return (i);
}

static char	*ft_get_substr(char const *s, char sep, int num)
{
	char	*str;
	int		start;
	int		stop;

	start = ft_find_substr(s, sep, num);
	if (start < 0)
		return (NULL);
	stop = start + 1;
	while (s[stop] && s[stop] != sep)
		stop ++;
	str = ft_substr(s, start, stop);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	int		nb_substr;
	int		i;

	nb_substr = ft_count_str(s, c);
	str_array = malloc(sizeof (char *) * (nb_substr + 1));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	while (i < nb_substr)
	{
		str_array[i] = ft_get_substr(s, c, i);
		i ++;
	}
	str_array[i] = NULL;
	return (str_array);
}
