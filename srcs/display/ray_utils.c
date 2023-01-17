#include <cub3d.h>

void	get_ray_angle_old(t_mlx *mlx, double *angles)
{
	int		i;
	double	interval;

	//get min and max angle
	angles[0] = mlx->player.direction - (FOV/2);
	angles[WIN_W -1] = mlx->player.direction + (FOV/2);
	//calculate interval between each angle (max-min + fov)
	interval = (angles[WIN_W - 1] - angles[0]) / WIN_W;
	//iterate through the range and get each ray
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
 * 		seg_len = half_screenlen / (WIN_W/2)
 * 		with half_screenlen = tan(FOV/2)
 * 		(we might have seg_len = (tan(FOV)) /WIN_W)
 *
 * 		then the TOA of soh-cah-toa give angle=tan((seglen*nb_seg)/screen_dist)
 * 		
 */

//angle = arctan(opposite/adjacent)

void	get_ray_angle(t_mlx *mlx, double *angles)
{
	int				i;
	double			seglen; //the distance, on the screen, between each column

	if (FOV >= M_PI || FOV <= -M_PI)
	{
		get_ray_angle_old(mlx, angles);
		return;
	}
	angles += WIN_W/2;
	//calculate seglen = SCREEN_DIST * tan(FOV/WIN_W)
	seglen = tan(FOV/WIN_W);
	i = -WIN_W/2;
	while (i < WIN_W/2)
	{
		angles[i] = mlx->player.direction + atan((i)*seglen);
		i ++;
	}
}



/* function that, once a wall is found, fill the wall data structure
 * the struct is passed by reference, so there is no return value.
 * it ignore height parameter for now, as it will be filled later
 */
int	wall_info(t_wall_data *data, t_coord ray, int face, t_entity *player)
{
	data->distance = sqrt(pow(player->pos_x - ray.x, 2) +
		pow(player->pos_y - ray.y, 2));
	//little modif to avoid infinit height wall :
	if (data->distance < 0.1)
		data->distance = 0.1;
	data->side = face;
	data->pos=ray;
	return (1);
}
