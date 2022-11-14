/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:57:49 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/10 17:03:36 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* function that convert a string into an int, using the base in parameter.
 * this function include limited security concerning the base, as it should
 * not be up to the user to determine what base to converte from.
 * dev, if you fuck up and put random stuff (duplicate char...), that's on you.
 */
unsigned int	ft_atoi_base(char *str, char *base_str)
{
	int	i;
	int	j;
	int	nb;
	int	base;

	nb = 0;
	if (!str || !base_str || ft_strlen(base_str) < 2)
		return (0);
	base = ft_strlen(base_str);
	i = 0;
	while (ft_isspace(str[i]))
		i ++;
	while (char_in_set(str[i], base_str))
	{
		nb *= base;
		j = 0;
		while (base_str[j] && str[i] != base_str[j])
			j ++;
		if (!base_str[j])
			return (nb);
		nb += j;
		i ++;
	}
	return (nb);
}
