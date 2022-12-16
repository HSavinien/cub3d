/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/15 23:59:21 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//the folowing are debug macros, meant to assignate a color to each wall.
//the color were sugested by chatgpt.
#define NORTH_C 0xF08080 //light red
#define SOUTH_C 0xADD8E6 //light blue
#define EAST_C 0xFFFFE0 //light yellow
#define WEST_C 0x90EE90 //light green

void	draw_wall(int ray_num, t_wall_data wall, t_mlx *mlx_s, t_img *screen)
{
	int	line;
	int column;

	column = 
	//get number of pixel based on height so that a wall is square when WALL_H=1
	//
}
