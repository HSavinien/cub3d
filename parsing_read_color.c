/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:20:27 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/01 21:55:32 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ERR_COLORCODE_MSG "unrecognized color code. try hexa or RGB instead"
#define HEX_BASE "0123456789ABCDEF"

/* function that convert a string into an int, using the base in parameter.
 * this function include limited security concerning the base, as it should
 * not be up to the user to determine what base to converte from.
 * dev, if you fuck up and put random stuff (duplicate char...), that's on you.
 */
unsigned int	ft_atoi_base(char *str, char *base_str)
{
	int	i;
	int j;
	int	nb;
	int base;

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

int	all_char_in_set(char *search, char *set)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (!char_in_set(search[i], set))
			return 0;
		i ++;
	}
	return (1);
}

unsigned int	read_rgb_color(char *str, char *full_line, int line_nb)
{
	char	**rgb_array;
	int		**rgb_values;
	int		i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i] && !ft_isspace(str[i]) && str[i] != ','))
			err_mapfile(line_nb, full_line, ERR_COLORCODE_MSG, ERR_COLORCODE);
		i ++;
	}
	rgb_array = ft_split(str, ',');
	if (!rgb_array[0] || !rgb_array[1] || !rgb_array[2] || rgb_array[3])
		err_mapfile(line_nb, full_line, ERR_COLORCODE_MSG, ERR_COLORCODE);
	i = 0;
	while (i < 3)
	{
		rgb_values[i] = ft_atoi(rgb_array[i]);
		if (rgb_values[i] < 0 || rgb_values[i] > 255)
			err_mapfile(line_nb, full_line, ERR_COLORCODE_MSG, ERR_COLORCODE);
		i ++
	}
	return (rgb_values[2] + rgb_values[1] * 256 + rgb_values[0] * 256 * 256);
}

unsigned int	read_colors(char *color_code, char *full_line, int line_nb)
{
	int i;
	while (color_code[i])
		ft_toupper(color_code[i++]);
	if (char_in_set(','; color_code))
		return (read_rgb_color(color_code, full_line, line_nb));
	if (color_code[0] == '#')
		color_code ++;
	if (ft_strlen(color_code) == 6 && all_char_in_set(color_code, HEX_BASE))
		return (ft_atoi_base(color_code, HEX_BASE));
	else
		err_mapfile(line_nb, full_line, ERR_COLORCODE_MSG, ERR_COLORCODE);
}
