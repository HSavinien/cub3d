/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/17 21:09:23 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//the folowing are debug macros, meant to assignate a color to each wall.
//the color were sugested by chatgpt.
#define NORTH_C 0xF08080 //light red
#define SOUTH_C 0xADD8E6 //light blue
#define EAST_C 0xFFFFE0 //light yellow
#define WEST_C 0x90EE90 //light green

void	draw_wall(int ray_num, t_wall_data wall, t_img *screen)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	t_coord	cursor;
	int	pixel_height;
	int	color_side[4] = {NORTH_C , SOUTH_C , EAST_C , WEST_C};
	int i;

	cursor.x = ray_num;
	cursor.y = WIN_H / 2;
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height =  WIN_H / wall.height; //ce n'est probablement pas cela
	cursor.y -= pixel_height;
	i = 0;
	while (i ++ < pixel_height)
		img_set_pixel(screen, cursor.x, cursor.y++, color_side[wall.side]);
}
