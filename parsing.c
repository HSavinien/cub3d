/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/02 23:14:03 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ERR_FILE_OPEN_MSG " could not be oppened. Check the file name and rights"
#define ERR_LINE_MSG "the line don't match any known patern"
#define MSG_OMAP "the map is open. Please close the map."
#define ERR_MLTPLR_MSG "multiple player spawn detected"
#define ERR_MAP_CHAR_MSG "ilegal character found in map token"

void	check_file_name(char *name)
{
	char	*cut_name;

	cut_name = ft_strrchr(name, '/');
	if (cut_name)
		cut_name += 1;
	else
		cut_name = name;
	if (ft_strcmp(cut_name + ft_strlen(cut_name) - 4, ".cub"))
		ft_error("map name must be in '.cub' format", ERR_EXTENTION);
	else if (ft_strlen(cut_name) <= 4)
		ft_error("map name look empty", ERR_SHORT_NAME);
}

//initialy called check_border, renamed because norm de ses mort
unsigned char	chkbrdr(int line, int col, int nb_line, char **map)
{
	int	i;
	int	j;

	if (!line || line == nb_line || !col ||
		col == (int) ft_strlen(map[line]))
		err_map_form(line, col, map, MSG_OMAP, ERR_OPEN_MAP);
	i = -1;
	while (i < 2)
	{
		j = -1;
		while (j < 2)
		{
			if (char_in_set(map[line + i][col + j], " \n"))
				err_map_form(line, col, map, MSG_OMAP, ERR_OPEN_MAP);
			j ++;
		}
		i ++;
	}
	return (FLOOR);
}

void	check_map_char(char **raw_map, int i, int j, t_map *map_s)
{
	static int	nb_player = 0;

	if (char_in_set(raw_map[i][j], "NSEW"))
	{
		if (nb_player ++)
			err_map_form(i, j, map_s->raw_map, ERR_MLTPLR_MSG, ERR_MULTIPLAYER);
		map_s->start_line = i;
		map_s->start_column = j;
		map_s->start_dir = raw_map[i][j];
		raw_map[i][j] = '0';
	}
	if (char_in_set(raw_map[i][j], "1 \n"))
		map_s->parsed_map[i][j] = (t_uchar) WALL;
	else if (raw_map[i][j] == '0')
		map_s->parsed_map[i][j] = chkbrdr(i, j, map_s->nb_line, map_s->raw_map);
	else
		err_map_form(i, j, map_s->raw_map, ERR_MAP_CHAR_MSG, ERR_MAP_CHAR);
}

void	parse_map_data(t_map *map_s)
{
	char			**raw_map;
	int				i;
	int				j;

	raw_map = map_s->raw_map;
	i = 0;
	while (raw_map[i])
		i ++;
	map_s->parsed_map = ft_calloc(sizeof(unsigned char *), i + 1);
	i = 0;
	while (raw_map[i])
	{
		j = 0;
		while (raw_map[i][j])
			j ++;
		map_s->parsed_map[i] = ft_calloc(sizeof(unsigned char), j + 1);
		j = 0;
		while (raw_map[i][j])
		{
			check_map_char(raw_map, i, j ++, map_s);
		}
		i ++;
	}
}

t_map	*parsing(char	*map_file)
{
	int		map_fd;
	t_map	*map_s;

	check_file_name(map_file);
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		ft_error(ft_strjoin(map_file, ERR_FILE_OPEN_MSG), ERR_OPEN);
	map_s = ft_calloc(sizeof(t_map), 1);
	if (!map_s)
		ft_error("unexpected malloc error in parsing", ERR_MALLOC);
	read_cub_file(map_fd, map_s);
	parse_map_data(map_s);
	check_missing_data(map_s);
	return (map_s);
}
