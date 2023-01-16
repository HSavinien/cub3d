/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/16 18:30:20 by tmongell         ###   ########.fr       */
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
int	get_pixel_color(int draw_line, int draw_height, t_wall_data *wall)
{
	int	img_line;
	int	color;

	//get line num in img
	img_line = 1.0*draw_line/draw_height * wall->texture->height;
	//extract draw data from image
	color = img_get_pixel(wall->texture, wall->texture_column, img_line);
		return (color & 0x00FFFFFF);
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
	double	modf_buff;
	
	//get number of pixel based on height so that a wall is square when WALL_H=1
	pixel_height = (wall.height * WIN_W/FOV);
	pos_y = ft_max(0, WIN_H/2 - pixel_height/2);
	get_wall_img(&wall, mlx);
	wall.texture = get_wall_img(&wall, mlx);
	if (wall.side == NORTH_FACE || wall.side == SOUTH_FACE)
		wall.texture_column = modf(wall.pos.x, &modf_buff) * wall.texture->width;
	else
		wall.texture_column = modf(wall.pos.y, &modf_buff) * wall.texture->width;
	i = ft_max(0, -pos_y);
	while (i ++ < pixel_height && pos_y < WIN_H)
	{
//		dprintf(2, "loop %d\n",i);//DEBUG
		if (pos_y > 0 && pos_y < WIN_H)
			img_set_pixel(screen, ray_num, pos_y, get_pixel_color(
			i - 1, pixel_height, &wall));
		pos_y ++;
	}
}

/* psychedelic lines : 
 
 * img_set_pixel(screen, ray_num, pos_y, (pos_y*ray_num) << (wall.side-1) | (i*ray_num <<16));
 
 */
