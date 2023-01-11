/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/11 23:30:31 by tmongell         ###   ########.fr       */
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

//need to know : ray_impact coordinate, img, pos_y, pixel height
int	get_pixel_color(int line, int height, t_img *ref_img, t_wall_data *wall)
{
	double	wall_column;
	int	img_column;
	int	img_line;

	//find where we are on wall
	if (wall->side == NORTH_FACE || wall->side == SOUTH_FACE)
		wall_column = wall->pos.x - floor(wall->pos.x);
	else
		wall_column = wall->pos.y - floor(wall->pos.y);
	//get column num in img
	img_column = ref_img->width * wall_column;
	//get line num in img
	img_line = ref_img->height * (line/height);
	//extract pixel data from image
	return (img_get_pixel(ref_img, img_column, img_line));
}

/*function that find which texture to use for the wall*/
t_img	*get_wall_img(t_wall_data *wall, t_mlx *mlx)
{
	int	side;	//stored in a var for faster memory access
	
	side = wall->side;
	if (side == NORTH_FACE)
		return (&mlx->sprites->north_wall);
	else if (side == SOUTH_FACE)
		return (&mlx->sprites->south_wall);
	else if (side == EAST_FACE)
		return (&mlx->sprites->east_wall);
	else if (side == WEST_FACE)
		return (&mlx->sprites->west_wall);
	else
		ft_error("error when fetching img for wall", ERR_WTF);
	return (NULL);
}

void	draw_wall_img(int ray_num, t_wall_data wall, t_img *screen, t_mlx *mlx)
{
	int		pos_y;
	int		pixel_height;
	int 	i;
	
	pos_y = WIN_H / 2;
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height = (wall.height * WIN_W/FOV);
	pos_y -= pixel_height/2;
	i = ft_max(0, -pos_y);
	pos_y = ft_max(0, pos_y);
	while (i ++ < pixel_height && pos_y < WIN_H)
	{
		if (pos_y > 0 && pos_y < WIN_H)
			img_set_pixel(screen, ray_num, pos_y, get_pixel_color(
			pos_y, pixel_height, get_wall_img(&wall, mlx), &wall));
		pos_y ++;
	}
}
