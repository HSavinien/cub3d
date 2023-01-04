/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/04 18:09:59 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//the folowing are debug macros, meant to assignate a color to each wall.
//the color were sugested by chatgpt.
/*
#define NORTH_C 0xF08080 //light red
#define SOUTH_C 0xADD8E6 //light blue
#define EAST_C 0xFFFFE0 //light yellow
#define WEST_C 0x90EE90 //light green
*/
#define NORTH_C 0xFF0000 //red
#define SOUTH_C 0xFF //blue
#define EAST_C 0xFFFF00 //yellow
#define WEST_C 0xFF00 //green

void	draw_wall(int ray_num, t_wall_data wall, t_img *screen)
{
	int	line;
	int	pixel_height;
	int	color_side[4] = {NORTH_C , SOUTH_C , EAST_C , WEST_C};
	int i;

	line = WIN_H / 2;
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height = wall.height * WIN_H; //ce n'est probablement pas cela
	if (pixel_height >= WIN_H)
		pixel_height = WIN_H;
	line -= pixel_height/2;
	i = 0;
	while (i ++ < pixel_height)
	{
		if (line >= 0 && line < WIN_H)
			img_set_pixel(screen, ray_num, line++, color_side[wall.side - 1]);
	}
}
