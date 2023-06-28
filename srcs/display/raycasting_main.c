/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2023/06/08 15:47:24 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that check if the ray coordinate are against a wall.
 * if it is against a wall, it fill the data structure and return 1.
 * else, it return 0;
 */
int	check_wall(t_coord ray, t_map *map, t_wall_data *data, t_entity *player)
{
	int	ret_val;

	ret_val = 0;
	if (ray.x - floor(ray.x) <= EPSILON)
	{
		if (ray.x >= 1 && map->parsed_map[(int)ray.y][(int)ray.x - 1] != FLOOR)
			ret_val = wall_info(data, ray, get_type(
						map, ray.x - 1, ray.y, WEST_FACE), player);
		if (map->parsed_map[abs((int)ray.y)][(int)ray.x] != FLOOR)
			ret_val = wall_info(data, ray, get_type(
						map, ray.x, ray.y, EAST_FACE), player);
	}
	if (ray.y - floor(ray.y) <= EPSILON)
	{
		if (ray.y >= 1 && map->parsed_map[(int)ray.y - 1][(int)ray.x] != FLOOR)
			ret_val = wall_info(data, ray, get_type(
						map, ray.x, ray.y - 1, NORTH_FACE), player);
		if (map->parsed_map[abs((int)ray.y)][(int)ray.x] != FLOOR)
			ret_val = wall_info(data, ray, get_type(
						map, ray.x, ray.y, SOUTH_FACE), player);
	}
	return (ret_val);
}

t_wall_data	find_wall(double angle, t_coord start, t_entity *player, t_map *map)
{
	t_wall_data	wall_s;
	t_coord		ray;
	double		slope;
	double		offset;

	ft_bzero(&wall_s, sizeof(t_wall_data));
	slope = tan(angle);
	offset = start.y - slope * start.x;
	ray = start;
	if (start.x != player->pos_x || start.y != player->pos_y)
		get_next_pos(&ray, angle, slope, offset);
	while (!check_wall(ray, map, &wall_s, player))
		get_next_pos(&ray, angle, slope, offset);
	return (wall_s);
}

void	cast_ray(t_cast_data data, t_coord start, t_img *screen, t_mlx *mlx)
{
	t_wall_data	wall_s;
	t_coord		restart;

	wall_s = find_wall(data.angle, start, &mlx->player, mlx->map_s);
	wall_s.distance *= fabs(cos(data.angle - mlx->player.direction));
	wall_s.height = (DEPTH / wall_s.distance);
	if (wall_s.side == DOOR_OP_FACE || wall_s.side == DOOR_CL_FACE)
	{
		restart = wall_s.pos;
		cast_ray(data, wall_s.pos, screen, mlx);
	}
	draw_wall_img(data.ray_num, wall_s, screen, mlx);
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];
	t_coord	start;

	get_ray_angle(mlx, ray_angles);
	start.x = mlx->player.pos_x;
	start.y = mlx->player.pos_y;
	i = 0;
	while (i < WIN_W)
	{
		cast_ray((t_cast_data){ray_angles[i], i}, start, screen, mlx);
		i ++;
	}
}
