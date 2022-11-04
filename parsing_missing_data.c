/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_missing_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:26:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/04 18:04:29 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define NMAP "your map file is missing some usefull data, like THE F**KING MAP!"
#define MSG_DUP "data redefined. the same entry can't appear twice in one file"

void	check_display_info(t_map *map)
{
	if (!map->north_path)
		ft_error("missing texture path for north wall", ERR_MISSING_DATA);
	if (!map->south_path)
		ft_error("missing texture path for south wall", ERR_MISSING_DATA);
	if (!map->east_path)
		ft_error("missing texture path for east wall", ERR_MISSING_DATA);
	if (!map->west_path)
		ft_error("missing texture path for west wall", ERR_MISSING_DATA);
	if (!map->floor_color)
		ft_error("missing color for floor", ERR_MISSING_DATA);
	if (!map->roof_color)
		ft_error("missing color for ceiling", ERR_MISSING_DATA);
}

void	check_player_info(t_map *map)
{
	if (!map->start_dir)
		ft_error("there is no player start point. please add it to the map",
			ERR_MISSING_DATA);
}

void	check_missing_data(t_map *map)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	dprintf(2, "north wall : %s\n", map->north_path);//DEBUG
	dprintf(2, "south wall : %s\n", map->south_path);//DEBUG
	dprintf(2, "east wall : %s\n", map->east_path);//DEBUG
	dprintf(2, "west wall : %s\n", map->west_path);//DEBUG
	dprintf(2, "floor color : #%X\n", map->floor_color);//DEBUG
	dprintf(2, "ceiling color : #%X\n", map->roof_color);//DEBUG
	check_display_info(map);
	dprintf(2, "\033[32mdisplay info OK\033[0m\n");//DEBUG
	if (!map->raw_map)
		ft_error(NMAP, ERR_MISSING_DATA);
	dprintf(2, "\033[32mmap info OK\033[0m\n");//DEBUG
	check_player_info(map);
	dprintf(2, "\033[32mplayer info OK\033[0m\n");//DEBUG
}

void	check_duplicate(char *id, char *line, int line_num, t_map *map_s)
{
	if (
			(ft_strcmp(id, "NO") && map_s->north_path) ||
			(ft_strcmp(id, "SO") && map_s->south_path) ||
			(ft_strcmp(id, "EA") && map_s->east_path) ||
			(ft_strcmp(id, "WE") && map_s->west_path) ||
			(ft_strcmp(id, "C") && map_s->roof_color) ||
			(ft_strcmp(id, "F") && map_s->floor_color))
		err_mapfile(line_num, line, MSG_DUP, ERR_DUPLICATE);
}
