/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:56:48 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/19 02:06:30 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//need to know : ray_impact coordinate, img, pos_y, pixel height
int	get_pixel_color(int draw_line, int draw_height, t_wall_data *wall)
{
	int	img_line;
	int	color;

	img_line = 1.0 * draw_line / draw_height * wall->texture->height;
	color = img_get_pixel(wall->texture, wall->texture_col, img_line);
	return (color);
}

/*function that find which texture to use for the wall*/
t_img	*get_wall_img(t_wall_data *wall, t_mlx *mlx)
{
	int	side;

	side = wall->side;
	if (side == NORTH_FACE)
		return (&mlx->sprites->north_wall);
	else if (side == SOUTH_FACE)
		return (&mlx->sprites->south_wall);
	else if (side == EAST_FACE)
		return (&mlx->sprites->east_wall);
	else if (side == WEST_FACE)
		return (&mlx->sprites->west_wall);
	else if (side == DOOR_CL_FACE)
		return (&mlx->sprites->door_closed);
	else if (side == DOOR_OP_FACE)
		return (&mlx->sprites->door_opened);
	else
		ft_error("error when fetching img for wall", ERR_WTF);
	return (NULL);
}

void	draw_wall_img(int ray_num, t_wall_data wall, t_img *screen, t_mlx *mlx)
{
	int		pos_y;
	int		pixel_height;
	int		i;
	double	modf_buff;

	wall.texture = get_wall_img(&wall, mlx);
	wall.texture_col = fmax(modf(wall.pos.x, &modf_buff),
			modf(wall.pos.y, &modf_buff)) * wall.texture->width;
	pixel_height = (wall.height * WIN_W / FOV);
	pos_y = ft_max(0, WIN_H / 2 - pixel_height / 2);
	i = -ft_min(0, WIN_H / 2 - pixel_height / 2);
	while (i ++ < pixel_height && pos_y < WIN_H)
	{
		if (pos_y > 0 && pos_y < WIN_H)
			img_set_pixel(screen, ray_num, pos_y,
				get_pixel_color(i - 1, pixel_height, &wall));
		pos_y ++;
	}
}

/* psychedelic lines :  
img_set_pixel(screen, ray_num, pos_y, (pos_y*ray_num) << (wall.side-1) |
(i*ray_num <<16));
 
 */
