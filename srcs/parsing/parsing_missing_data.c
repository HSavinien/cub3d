/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_missing_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:26:03 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/18 19:51:10 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (map->floor_color < 0)
		ft_error("missing color for floor", ERR_MISSING_DATA);
	if (map->roof_color < 0)
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
	check_display_info(map);
	if (!map->raw_map)
		ft_error(MSG_MAP, ERR_MISSING_DATA);
	check_player_info(map);
}

void	check_duplicate(char *id, char *line, int line_num, t_map *map_s)
{
	if (!ft_strcmp(id, "NO") && map_s->north_path)
		err_mapfile(line_num, line, "duplicate north texture", ERR_DUPLICATE);
	if (!ft_strcmp(id, "SO") && map_s->south_path)
		err_mapfile(line_num, line, "duplicate south texture", ERR_DUPLICATE);
	if (!ft_strcmp(id, "EA") && map_s->east_path)
		err_mapfile(line_num, line, "duplicate east texture", ERR_DUPLICATE);
	if (!ft_strcmp(id, "WE") && map_s->west_path)
		err_mapfile(line_num, line, "duplicate west texture", ERR_DUPLICATE);
	if (!ft_strcmp(id, "C") && map_s->roof_color >= 0)
		err_mapfile(line_num, line, "duplicate ceiling color", ERR_DUPLICATE);
	if (!ft_strcmp(id, "F") && map_s->floor_color >= 0)
		err_mapfile(line_num, line, "duplicate floor color", ERR_DUPLICATE);
	if (!ft_strcmp(id, "CR") && map_s->crosshair)
		err_mapfile(line_num, line, "duplicate crosshair image", ERR_DUPLICATE);
	if (!ft_strcmp(id, "DC") && map_s->door_closed)
		err_mapfile(line_num, line, "duplicate closed door", ERR_DUPLICATE);
	if (!ft_strcmp(id, "DO") && map_s->door_opened)
		err_mapfile(line_num, line, "duplicate opened door", ERR_DUPLICATE);
}
