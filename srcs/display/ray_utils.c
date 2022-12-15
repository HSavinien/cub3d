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
