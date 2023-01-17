/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/17 14:35:10 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MSG_FILE_OPEN " could not be oppened. Check the file name and rights."
#define MSG_LINE "the line don't match any known patern."
#define MSG_OMAP "the map is open. Please close the map."
#define MSG_MLTPLR "multiple player spawn detected."
#define MSG_MAP_CHAR "ilegal character found in map token."
#define MSG_FILE_DIR "map should be a file, not a directory. change your file."

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
unsigned char	chkbrdr(int ln, int col, int nbln, char **map)
{
	int	len;
	int	pos[2];

	len = ft_strlen(map[ln]) - 1;
	pos[0] = ln;
	pos[1] = col;
	nbln --;
	if (ln <= 0 || ln >= nbln || col <= 0 || col >= (int)ft_strlen(map[ln]) - 1)
		err_map_form(pos, map, MSG_OMAP, ERR_OPEN_MAP);
	if (col > ft_min(ft_strlen(map[ln - 1]), ft_strlen(map[ln + 1])))
		err_map_form(pos, map, MSG_OMAP, ERR_OPEN_MAP);
	else if (ln <= 0 || char_in_set(map[ln - 1][col], " \t\n"))
		pos[0] = ft_max(ln -1, 0);
	else if (ln >= nbln || char_in_set(map[ln + 1][col], " \t\n"))
		pos[0] = ft_min(ln +1, nbln);
	else if (col <= 0 || (char_in_set(map[ln][col - 1], " \t\n")))
		pos[1] = ft_max(col -1, 0);
	else if (col >= len || char_in_set(map[ln][col + 1], " \t\n"))
		pos[1] = ft_min(col +1, len);
	else
		return (FLOOR);
	err_map_form(pos, map, MSG_OMAP, ERR_OPEN_MAP);
	return (0);
}

void	check_map_char(char **raw_map, int i, int j, t_map *map_s)
{
	static int	nb_player = 0;
	int			pos[2];

	pos[0] = i;
	pos[1] = j;
	if (char_in_set(raw_map[i][j], "NSEW"))
	{
		if (nb_player ++)
			err_map_form(pos, map_s->raw_map, MSG_MLTPLR, ERR_MULTIPLAYER);
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
		err_map_form(pos, map_s->raw_map, MSG_MAP_CHAR, ERR_MAP_CHAR);
}

void	parse_map_data(t_map *map_s)
{
	char			**raw_map;
	int				i;
	int				j;

	raw_map = map_s->raw_map;
	i = 0;
	while (raw_map && raw_map[i])
		i ++;
	map_s->parsed_map = ft_calloc(sizeof(unsigned char *), i + 1);
	i = 0;
	while (raw_map && raw_map[i])
	{
		j = 0;
		while (raw_map[i][j])
			j ++;
		map_s->parsed_map[i] = ft_calloc(sizeof(unsigned char), j + 10);
		j = 0;
		while (raw_map[i][j])
			check_map_char(raw_map, i, j ++, map_s);
		i ++;
	}
	if (map_s->start_line)
		raw_map[map_s->start_line][map_s->start_column] = '0';
}

t_map	parsing(char	*map_file)
{
	int		map_fd;
	t_map	map_s;

	check_file_name(map_file);
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		ft_error(ft_strjoin(map_file, MSG_FILE_OPEN), ERR_OPEN);
	ft_bzero(&map_s, sizeof(map_s));
	map_s.floor_color = -1;
	map_s.roof_color = -1;
	read_cub_file(map_fd, &map_s);
	parse_map_data(&map_s);
	check_missing_data(&map_s);
	close(map_fd);
	return (map_s);
}
