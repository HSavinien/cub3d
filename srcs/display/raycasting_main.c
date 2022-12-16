/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/16 00:03:28 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

	find_wall	(double angle, t_wall_data data, t_entity *player, t_map *map)
{
	double	ray_x;
	double	ray_y;
	double	slope;
	double	offset;
	//get ray_equation (form y=ax+b)
		// with a=tan(angle) ; b = player_y - a * player_x
	slope = tan(angle);
	offset = player->pos_y - slope * player->pos_x;
	//init ray position;
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	//while no wall found and didn't left map area
	while (ray_x >= 0 && ray_x <= nb_column && ray_y >= 0 && ray_y <= nb_line)
	{
		// get the next entire x; calculate equivalent y;
		// if entire part of new y 
		//check if there is a wall on either side of the point
		//if there is a wall, fill struct and return it.
	}
}

void	cast_ray(double angle, int ray_num, t_img *screen, t_mlx *mlx)
{
	t_wall_data	wall_s;

	//find next wall
	find_wall(angle, &wall_s, &mlx.player, mlx->map_s);
	//use trigo/pythagore to calculate 'straight' distance (anti fish eye)
	wall_s.distance = len * sin(angle - mlx->player->direction)
	//calculate wall height
	wall_s.height = WALL_H / (wall_s.distance * DEPTH);
	//if jump is implemented, it goes there--------------------------------------JUMP
	//fill image with pixel column;
	draw_wall(ray_num, wall_s, mlx, screen);
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];	//list the angle of each ray, in rad


	//calculate the angle of each ray
	get_ray_angle(mlx, &ray_angle);
	i = 0;
	while (i < WIN_W)
		cast_ray(ray_angles[i ++], i, screen, mlx);
}
