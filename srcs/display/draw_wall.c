/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/18 15:00:05 by tmongell         ###   ########.fr       */
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
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	//dprintf(2, "ray num %d, wall at [%f,%f](dist %f, height %f)\n",
//		ray_num, wall.pos.x, wall.pos.y, wall.distance, wall.height);//DEBUG
	int	line;
	int	pixel_height;
	int	color_side[4] = {NORTH_C , SOUTH_C , EAST_C , WEST_C};
	int i;

	line = WIN_H / 2;
	//dprintf(2, "inited cursor\n");//DEBUG
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height = wall.height * WIN_H; //ce n'est probablement pas cela
//	dprintf(2, "true height %f, pixel height %d\n", wall.height, pixel_height);//DEBUG
	//dprintf(2, "height in pixel : %d\n", pixel_height);//DEBUG
	line -= pixel_height;
	line = ft_max(line, 0);
	//dprintf(2, "start pixel : %d,%d\n", ray_num, line);//DEBUG
	i = 0;
	while (i ++ < pixel_height && line < WIN_H)
		img_set_pixel(screen, ray_num, line++, color_side[wall.side]);
}
