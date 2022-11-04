/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/04 17:10:18 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MSG_FILE_OPEN " could not be oppened. Check the file name and rights"
#define MSG_LINE "the line don't match any known patern"
#define MSG_OMAP "the map is open. Please close the map."
#define MSG_MLTPLR "multiple player spawn detected"
#define MSG_MAP_CHAR "ilegal character found in map token"

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
unsigned char	chkbrdr(int line, int col, int nbln, char **map)
{
	int	len;

	len = ft_strlen(map[line]) - 1;
	nbln --;
	if (col > ft_min(ft_strlen(map[line - 1]), ft_strlen(map[line + 1])))
		err_map_form(line, col, map, MSG_OMAP, ERR_OPEN_MAP);
	if (line <= 0 || char_in_set(map[line - 1][col], " \t\n")) //top check
		err_map_form(ft_max(line - 1, 0), col, map, MSG_OMAP, ERR_OPEN_MAP);
	if (line >= nbln || char_in_set(map[line + 1][col], " \t\n")) //botom check
		err_map_form(ft_min(line + 1, nbln), col, map, MSG_OMAP, ERR_OPEN_MAP);
	if (col <= 0 || char_in_set(map[line][col - 1], " \t\n")) //left check
		err_map_form(line, ft_max(col - 1, 0), map, MSG_OMAP, ERR_OPEN_MAP);
	if (col >= len || char_in_set(map[line][col + 1], " \t\n")) //right check
		err_map_form(line, ft_min(col + 1, len), map, MSG_OMAP, ERR_OPEN_MAP);
	return (map[line][col]);
}

void	check_map_char(char **raw_map, int i, int j, t_map *map_s)
{
	static int	nb_player = 0;

	if (char_in_set(raw_map[i][j], "NSEW"))
	{
		if (nb_player ++)
			err_map_form(i, j, map_s->raw_map, MSG_MLTPLR, ERR_MULTIPLAYER);
		map_s->start_line = i;
		map_s->start_column = j;
		map_s->start_dir = raw_map[i][j];
		map_s->parsed_map[i][j] = chkbrdr(i, j, map_s->nb_line, map_s->raw_map);
	}
	else if (char_in_set(raw_map[i][j], "1 \n"))
		map_s->parsed_map[i][j] = (t_uchar) WALL;
	else if (raw_map[i][j] == '0')
		map_s->parsed_map[i][j] = chkbrdr(i, j, map_s->nb_line, map_s->raw_map);
	else
		err_map_form(i, j, map_s->raw_map, MSG_MAP_CHAR, ERR_MAP_CHAR);
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
			check_map_char(raw_map, i, j ++, map_s);
		i ++;
	}
	if (map_s->start_line)
		raw_map[map_s->start_line][map_s->start_column] = '0';
}

t_map	*parsing(char	*map_file)
{
	int		map_fd;
	t_map	*map_s;

	check_file_name(map_file);
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		ft_error(ft_strjoin(map_file, MSG_FILE_OPEN), ERR_OPEN);
	map_s = ft_calloc(sizeof(t_map), 1);
	if (!map_s)
		ft_error("unexpected malloc error in parsing", ERR_MALLOC);
	read_cub_file(map_fd, map_s);
	parse_map_data(map_s);
	check_missing_data(map_s);
	return (map_s);
}
