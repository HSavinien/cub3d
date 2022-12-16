#include <cub3d.h>

/* function that return an array of WIN_W double.
 * each value in the array represent the angle of the coresponding ray to cast.
 */
void	get_ray_angle(t_mlx *mlx, double *angles)
{
	int		i;
	double	interval;

	//get min and max angle
	angles[0] = mlx->player.direction - (FOV/2);
	angles[WIN_W -1] = mlx->player.direction + (FOV/2);
	//calculate interval between each angle (max-min + fov)
	interval = angles[WIN_W - 1] - angles[0] + FOV;
	//iterate through the range and get each ray
	i = 0;
	while (++i < WIN_W)
		angles[i] = angles[i -1] + interval;
}

/* function that, once a wall is found, fill the wall data structure
 * the struct is passed by reference, so there is no return value.
 * it ignore height parameter for now, as it will be filled later
 */
int	wall_info(t_wall_data *data, t_coord ray, int face, t_entity *player)
{
	data->distance = sqrt(pow(player->pos_x - ray.x, 2) +
		pow(player->pos_y - ray.y, 2));
	data->orientation = face;
	data->pos=ray;
	return (1);
}

/* function that get the next x or y on the direction line */
void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	//	y = slope * x + offset;
	//	from 180 include to 360 non include
	if (dir > 0.0 && (dir * (180.0) / M_PI) < 180.0)
		ray->y = (int)ray->y - 1.0;
	// from 0 include to -180 non include
	else if (dir < 0.0 && (dir * (180.0) / M_PI) > 180.0)
		ray->y = (int)ray->y + 1.0;
	ray->x = (ray->y) - offset / slope;
	if (dir == 0.0)
		ray->x += 1;
	 else if ((dir * (180.0) / M_PI) == 180.0)
		ray->x -= 1;
}
