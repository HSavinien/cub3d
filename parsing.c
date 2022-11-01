/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/01 22:10:19 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ERR_OPEN_MSG " could not be oppened. check the file name and rights"
#define ERR_LINE_MSG "the line don't match any known patern"
#define ERR_MULTIPLAYER_MSG "multiple player spawn detected"
#define ERR_MAP_CHAR "ilegal character found in map token"
#define ERR_MAP_OPEN_MSG "map must be closed"

void	check_file_name(char *name)
{
	char    *cut_name;

    cut_name = ft_strrchr(name, '/') + 1;
	if (!cut_name)
		cut_name = name;
	if (ft_strcmp(cut_name + ft_strlen(cut_name) - 4, ".cub"))
		ft_error("map name must be in '.cub' format", ERR_EXTENTION);
	else if (ft_strlen(cut_name) <= 4)
		ft_error("map name look empty", ERR_SHORT_NAME);
}

unsigned char	check_border(int line, int column, char **map)
{
	int	i;
	int	j;

	if (!line || line == nb_line || !column || column == ft_strlen(map[line]))
		err_map_form(line, column, map, ERR_OPEN_MAP_MSG, ERR_OPEN_MAP);
	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
		if (!charinset(map[line + i - 1][column + i - 1], "10NSEW"))
			err_map_form(line, column, map, ERR_OPEN_MAP_MSG, ERR_OPEN_MAP);
		}
	}
	return (FLOOR);
}

int	check_map_char(char **raw_map, int i, int j, t_map *map_struct)
{
	static int nb_player = 0;
	//if it's the player start, init player info and put a ground in base map.
	if (char_in_set(raw_map[i][j], "NSEW"))
	{
		if (nb_player ++)
			err_map_form(i, j, raw_map, ERR_MULTIPLAYER_MSG, ERR_MULTIPLAYER);
		map_struct->start_line = i;
		map_struct->start_column = j;
		map_struct->start_dir = raw_map[i][j];
		raw_map[i][j] = '0';
	}
	if (char_in_set(raw_map[i][j], "1 \n"))
		map_struct->parsed_map = WALL;
	else if (raw_map[i][j] == '0')
		map_struct->parsed_map = check_border(i, j, raw_map);
	else
		err_map_form(i, j, raw_map, ERR_MAP_CHAR_MSG, ERR_MAP_CHAR);
}

void	parse_map_data(t_map *map_struct)
{
	char			**raw_map;
	unsigned char	**parsed_map;
	int 			i;
	int				j;

	raw_map = map_struct->raw_map;
	i = 0;
	while (raw_map[i])
		i ++;
	parsed_map = ft_calloc(sizeof(unsigned char *), i + 1);
	i = 0;
	while (raw_map[i])
	{
		j = 0;
		while (raw_map[i][j])
			j ++;
		parsed_map[i] = ft_calloc(sizeof(unsigned char, j + 1));
		j = 0;
		while (raw_map[i][j])
			parsed_map[i][j] = check_map_char(raw_map, i, j ++, map_struct);
		i ++;
	}
	map_struct->parsed_map = parsed_map;
}

t_map	*parsing(char	*map_file)
{
	int		map_fd;
	t_map	*map_struct;
	
	check_map_name(map_file);
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		ft_error(ft_strjoin(map_file, ERR_MAP_OPEN_MSG), ERR_MAP_OPEN);
	map_struct = ft_calloc(sizeof(t_map));
	if (!map_struct)
		ft_error("unexpected malloc error in parsing", ERR_MALLOC);
	read_cub_file(fd, map_struct);
	parse_map_data(map_struct);
	check_missing_data(map_struct);
	return (map);
}
