/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:18:53 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/04 23:27:00 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	show_struct(t_map *map_s)
{
	dprintf(2, "NO : %s[%p]\n"
			"SO : %s[%p]\n"
			"EA : %s[%p]\n"
			"WE : %s[%p]\n"
			"C : %d[%p]\n"
			"F : %d[%p]\n",
			map_s->north_path, map_s->north_path,
			map_s->south_path, map_s->south_path,
			map_s->east_path, map_s->east_path,
			map_s->west_path, map_s->west_path,
			map_s->roof_color, &map_s->roof_color,
			map_s->floor_color, &map_s->floor_color);//DEBUG
}
