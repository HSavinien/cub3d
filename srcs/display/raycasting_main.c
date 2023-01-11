/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/11 23:29:43 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that check if the ray coordinate are against a wall.
 * if it is against a wall, it fill the data structure and return 1.
 * else, it return 0;
 */
int	check_wall(t_coord ray, t_map *map, t_wall_data *data, t_entity *player)
{
	if (ray.x - floor(ray.x) <= EPSILON) //case left and right to check
	{
		if (ray.x >= 1 && map->parsed_map[abs((int)ray.y)][(int)ray.x-1] == WALL)
			return (wall_info(data, ray, EAST_FACE, player));//found left wall -> east texture
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL)
			return (wall_info(data, ray, WEST_FACE,player));//found right wall -> west texture
	}
	if (ray.y - floor(ray.y) <= EPSILON)
	{
		if (ray.y >= 1 && map->parsed_map[abs((int)ray.y - 1)][(int)ray.x] == WALL) {
			return (wall_info(data, ray, NORTH_FACE,player));//found botom wall -> north texture
		}
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL) {
			return (wall_info(data, ray, SOUTH_FACE,player));//found top wall -> south texture
		}
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
	while (!check_wall(ray, map, data, player)) {
		get_next_pos(&ray, angle, slope, offset);
	}
}


t_wall_data	cast_ray(double angle, int ray_num, t_img *screen, t_mlx *mlx)
{
	t_wall_data	wall_s;

	//find next wall
	find_wall(angle, &wall_s, &mlx->player, mlx->map_s);
	//use trigo/pythagore to calculate 'straight' distance (anti fish eye)
	wall_s.distance *= fabs(cos(angle - mlx->player.direction));
	//calculate wall height
	wall_s.height = (DEPTH / wall_s.distance);
	//fill image with pixel column;
	draw_wall_img(ray_num, wall_s, screen, mlx);
	return(wall_s);
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
