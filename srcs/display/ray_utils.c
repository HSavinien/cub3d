/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:47:12 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/20 15:32:40 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_ray_angle_old(t_mlx *mlx, double *angles)
{
	int		i;
	double	interval;

	angles[0] = mlx->player.direction - (FOV / 2);
	angles[WIN_W -1] = mlx->player.direction + (FOV / 2);
	interval = (angles[WIN_W - 1] - angles[0]) / WIN_W;
	i = 0;
	while (++i < WIN_W - 1)
		angles[i] = angles[i -1] + interval;
}

/* function that return an array of WIN_W double.
 * each value in the array represent the angle of the coresponding ray to cast.
 * 
 * for geometric reason, successive angle must not be equal.
 * instead, the distance between two pixel column, on screen, must be the same.
 * as the screen is not cylindrical, regular angle don't work.
 *
 * we can calculate the len of a segment as : 
 * 		seglen = tan(FOV/WIN_W)
 */
void	get_ray_angle(t_mlx *mlx, double *angles)
{
	int				i;
	double			seglen;

	if (FOV >= M_PI || FOV <= -M_PI)
	{
		get_ray_angle_old(mlx, angles);
		return ;
	}
	angles += WIN_W / 2;
	seglen = tan(FOV / WIN_W);
	i = -WIN_W / 2;
	while (i < WIN_W / 2)
	{
		angles[i] = mlx->player.direction + atan((i) * seglen);
		i ++;
	}
}

int	get_type(t_map *map, int x, int y, int wall_side)
{
	if (map->parsed_map[y][x] == DOOR_CL)
		return (DOOR_CL_FACE);
	else if (map->parsed_map[y][x] == DOOR_OP)
		return (DOOR_OP_FACE);
	else
		return (wall_side);
}

/* function that, once a wall is found, fill the wall data structure
 * the struct is passed by reference, so there is no return value.
 * it ignore height parameter for now, as it will be filled later
 */
int	wall_info(t_wall_data *data, t_coord ray, int face, t_entity *player)
{
	data->distance = sqrt(pow(player->pos_x - ray.x, 2)
			+ pow(player->pos_y - ray.y, 2));
	if (data->distance < 0.1)
		data->distance = 0.1;
	data->pos = ray;
	data->side = face;
	return (1);
}
