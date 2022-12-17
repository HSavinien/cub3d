/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/17 15:06:44 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define NORTH_FACE 1
#define SOUTH_FACE 2
#define EAST_FACE 3
#define WEST_FACE 4

int	check_wall(t_coord ray, t_map *map, t_wall_data *data, t_entity *player)
{
	if (ray.x == floor(ray.x))
	{
		if (ray.x > 0 &&
			map->parsed_map[(int)ray.y][(int)ray.x - 1] == WALL)//wall on left
			return (wall_info(data, ray, EAST_FACE, player));
		if (ray.x < ft_strlen((char*)(map->parsed_map[(int)ray.y])) &&
			map->parsed_map[(int)ray.y][(int)ray.x + 1] == WALL)//wall on right
			return (wall_info(data, ray, WEST_FACE, player));
	}
	if (ray.y == floor(ray.y))
	{
		if (ray.y > 0 &&
			map->parsed_map[(int)ray.y - 1][(int)ray.x] == WALL)//wall above
			return (wall_info(data, ray, SOUTH_FACE, player));
		if (ray.y < map->nb_line &&
			map->parsed_map[(int)ray.y + 1][(int)ray.x] == WALL)//wall bellow
			return (wall_info(data, ray, NORTH_FACE, player));
	}
	return (0);
}

void	find_wall(double angle, t_wall_data *data, t_entity *player, t_map *map)
{
	t_coord	ray;
	double	slope;
	double	offset;
	//get ray_equation (form y=ax+b)
		// with a=tan(angle) ; b = player_y - a * player_x
	slope = tan(angle);
	offset = player->pos_y - slope * player->pos_x;
	//init ray position;
	ray.x = player->pos_x;
	ray.y = player->pos_y;
	//while no wall found and didn't left map area
	while (ray.x >= 0 && ray.x <= map->nb_column &&
		ray.y >= 0 && ray.y <= map->nb_line)
	{
		get_next_pos(&ray, player->direction, slope, offset);
		if (check_wall(ray, map, data, player))
			return;
	}
}

void	cast_ray(double angle, int ray_num, t_img *screen, t_mlx *mlx)
{
	t_wall_data	wall_s;

	//find next wall
	find_wall(angle, &wall_s, &mlx->player, mlx->map_s);
	//use trigo/pythagore to calculate 'straight' distance (anti fish eye)
	wall_s.distance = wall_s.distance * cos(angle - mlx->player.direction);
	//calculate wall height
	wall_s.height = WALL_H / (wall_s.distance * DEPTH);
	//if jump is implemented, it goes there--------------------------------------JUMP
	//fill image with pixel column;
	draw_wall(ray_num, wall_s, screen);
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];	//list the angle of each ray, in rad


	//calculate the angle of each ray
	get_ray_angle(mlx, ray_angles);
	i = 0;
	while (i < WIN_W)
	{
		cast_ray(ray_angles[i], i, screen, mlx);
		i ++;
	}
}
