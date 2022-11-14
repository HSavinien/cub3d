/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:18:53 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/14 16:28:05 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	show_struct(t_map *map_s)
{
	printf("NO : %s [%p]\n"
			"SO : %s [%p]\n"
			"EA : %s [%p]\n"
			"WE : %s [%p]\n"
			"C : %li [%p]\n"
			"F : %li [%p]\n",
			map_s->north_path, map_s->north_path,
			map_s->south_path, map_s->south_path,
			map_s->east_path, map_s->east_path,
			map_s->west_path, map_s->west_path,
			map_s->roof_color, &map_s->roof_color,
			map_s->floor_color, &map_s->floor_color);
}

void	show_map(char **map)
{
	printf("map at %p\n", map);
	if (map)
	{
		for(int i=0 ; map[i] ; i ++)
			printf("%s\n", map[i]);
	}
}
