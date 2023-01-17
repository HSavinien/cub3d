/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/17 14:09:29 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that check if the ray coordinate are against a wall.
 * if it is against a wall, it fill the data structure and return 1.
 * else, it return 0;
 */
int	check_wall(t_coord ray, t_map *map, t_wall_data *data, t_entity *player)
{
	if (ray.x - floor(ray.x) <= EPSILON)
	{
		if (ray.x >= 1 && map->parsed_map[abs((int)ray.y)][(int)ray.x - 1]
				== WALL)
			return (wall_info(data, ray, EAST_FACE, player));
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL)
			return (wall_info(data, ray, WEST_FACE, player));
	}
	if (ray.y - floor(ray.y) <= EPSILON)
	{
		if (ray.y >= 1 && map->parsed_map[abs((int)ray.y - 1)][(int)ray.x]
				== WALL)
			return (wall_info(data, ray, NORTH_FACE, player));
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL)
			return (wall_info(data, ray, SOUTH_FACE, player));
	}
	return (0);
}

void	find_wall(double angle, t_wall_data *data, t_entity *player, t_map *map)
{
	t_coord	ray;
	double	slope;
	double	offset;

	slope = tan(angle);
	offset = player->pos_y - slope * player->pos_x;
	ray.x = player->pos_x;
	ray.y = player->pos_y;
	while (!check_wall(ray, map, data, player))
		get_next_pos(&ray, angle, slope, offset);
}

t_wall_data	cast_ray(double angle, int ray_num, t_img *screen, t_mlx *mlx)
{
	t_wall_data	wall_s;

	find_wall(angle, &wall_s, &mlx->player, mlx->map_s);
	wall_s.distance *= fabs(cos(angle - mlx->player.direction));
	wall_s.height = (DEPTH / wall_s.distance);
	draw_wall_img(ray_num, wall_s, screen, mlx);
	return (wall_s);
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];

	get_ray_angle(mlx, ray_angles);
	i = 0;
	while (i < WIN_W)
	{
		cast_ray(ray_angles[i], i, screen, mlx);
		i ++;
	}
}
