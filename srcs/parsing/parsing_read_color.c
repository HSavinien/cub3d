/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:20:27 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/23 13:50:29 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	all_char_in_set(char *search, char *set)
{
	int	i;

	i = 0;
	while (search[i])
	{
		if (!char_in_set(search[i], set))
			return (0);
		i ++;
	}
	return (1);
}

void	check_valid_rgb(char *code, int line_nb, char *full_line)
{
	int	i;

	if (code[0] == ',')
		err_mapfile(line_nb, full_line, MSG_RGB_COMMA, ERR_COLORCODE);
	i = -1;
	while (code[++ i])
	{
		if (!ft_isdigit(code[i]) && !ft_isspace(code[i]) && code[i] != ',')
			err_mapfile(line_nb, full_line, MSG_COLORCODE, ERR_COLORCODE);
		if (code[i] == ',' && (code[i + 1] == ',' || !code[i + 1]))
			err_mapfile(line_nb, full_line, MSG_RGB_COMMA, ERR_COLORCODE);
	}
}

unsigned int	read_rgb_color(char *str, char *full_line, int line_nb)
{
	char	**rgb_array;
	char	*tmp_str;
	int		rgb_values[3];
	int		i;

	check_valid_rgb(str, line_nb, full_line);
	rgb_array = ft_split(str, ',');
	if (!rgb_array[0] || !rgb_array[1] || !rgb_array[2] || rgb_array[3])
		err_mapfile(line_nb, full_line, MSG_COLORCODE, ERR_COLORCODE);
	i = -1;
	while (++ i < 3)
	{
		rgb_values[i] = ft_atoi(rgb_array[i]);
		tmp_str = ft_strtrim(rgb_array[i], " \t\n");
		if (rgb_values[i] < 0 || rgb_values[i] > 255
			|| ft_strlen(tmp_str) > 3)
			err_mapfile(line_nb, full_line, MSG_COLORCODE, ERR_COLORCODE);
		free(tmp_str);
	}
	destroy_array(rgb_array);
	return (rgb_values[2] | rgb_values[1] << 8 | rgb_values[0] << 16);
}

//julia
//mandelbrot

unsigned int	read_color(char *color_code, char *full_line, int line_nb)
{
	int	i;

	i = -1;
	while (color_code[++ i])
		color_code[i] = ft_toupper(color_code[i]);
	if (!strcmp(color_code, "MANDELBROT"))
		return (MANDELBROT << 24);
	if (!strcmp(color_code, "JULIA"))
		return (JULIA << 24);
	if (char_in_set(',', color_code))
		return (read_rgb_color(color_code, full_line, line_nb));
	if (color_code[0] == '#')
		color_code ++;
	if (ft_strlen(color_code) == 6 && all_char_in_set(color_code, HEX_BASE))
		return (ft_atoi_base(color_code, HEX_BASE));
	else
		err_mapfile(line_nb, full_line, MSG_COLORCODE, ERR_COLORCODE);
	return (0);
}
