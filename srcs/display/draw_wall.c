/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/11 22:12:01 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*the two function draw_wall_plain and draw_wall_img are independente.
 * the first one put given colors on each walls, while the seconde put a texture
 * they should not be used at the same time, as they will write over each_other
 */

//the folowing are debug macros, meant to assignate a color to each wall.
//the color were sugested by chatgpt.
#define NORTH_C 0xFF0000 //red
#define SOUTH_C 0xFF //blue
#define EAST_C 0xFFFF00 //yellow
#define WEST_C 0xFF00 //green

void	draw_wall(int ray_num, t_wall_data wall, t_img *screen)
{
	int	pos_y;
	int	pixel_height;
	int	color_side[4] = {NORTH_C , SOUTH_C , EAST_C , WEST_C};
	int i;

	pos_y = WIN_H / 2;
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height = (wall.height * WIN_W/FOV);
	pos_y -= pixel_height/2;
	i = ft_max(0, -pos_y);
	pos_y = ft_max(0, pos_y);
	while (i ++ < pixel_height && pos_y < WIN_H)
	{
		if (pos_y >= 0 && pos_y < WIN_H)
			img_set_pixel(screen, ray_num, pos_y, color_side[wall.side - 1]);
		pos_y ++;
	}
}

