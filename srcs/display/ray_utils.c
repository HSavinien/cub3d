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

/* function that get the next x or y on the direction line */
void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	double		step_x;
	double		step_y;
	//	y = slope * x + offset;
	//	from 180 include to 360 non include
	if (dir == 0.0)
		ray->x += (int)ray->x + 1;
	else if ((dir * (180.0) / M_PI) == 180.0)
		ray->x += (int)ray->x - 1;
	step_x = fabs(ray->x - ceil(ray->x));
	step_y = fabs(ray->y - ceil(ray->y));
	if (dir > 0.0 && (dir * (180.0) / M_PI) < 180.0)
	{	
		step_x *= -1.0;
		step_y *= -1.0;
	}
	// from 0 include to -180 non include
	if (next_x < next_y && (dir != 0.0 || (dir * (180.0) / M_PI) != 180.0))
		ray->y = slope * round(ray->x + step_x) + offset;
	else if (next_x > next_y && (dir != 0.0 || (dir * (180.0) / M_PI) != 180.0))
		ray->x = round(ray->y + step_y) - offset / slope;
	}
}
