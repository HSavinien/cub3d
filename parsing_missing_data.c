/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_missing_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 22:26:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/01 22:26:05 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define NMAP "your map file is missing some usefull data, like THE F**KING MAP!"

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


void check_player_info(t_map *map)
{
	if (!map->start_dir)
		ft_error("there is no player start point. please add it to the map",
			ERR_MISSING_DATA);
}

void	check_missing_data(t_map *map)
{
	check_display_info(map);
	if (!raw_map)
		ft_error(NMAP, ERR_MISSING_DATA);
	check_player_info(map);
}
