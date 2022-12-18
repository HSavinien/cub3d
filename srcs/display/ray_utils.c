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
	interval = (angles[WIN_W - 1] - angles[0]) / WIN_W;
	//iterate through the range and get each ray
	i = 0;
	while (++i < WIN_W - 1)
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
	//little modif to avoid infinit height wall :
	if (data->distance < 0.1)
		data->distance = 0.1;
	data->side = face;
	data->pos=ray;
	return (1);
}

/*exception case of get_next_pos for when a ray is parrallel to an axis.
 */
void	advance_parallel_ray(t_coord *ray, double dir)
{
	if (cos(dir) == 1)
		ray->x = ceil(ray->x) + 1;
	else if (cos(dir) == -1)
		ray->x = floor(ray->x) - 1;
	else if (sin(dir) == 1)
		ray->y = ceil(ray->y) + 1;
	else if (sin(dir) == -1)
		ray->y = ceil(ray->y) - 1;
}

void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	int x_dir;
	int	y_dir;
	t_coord	next_x;
	t_coord	next_y;
	
	//check case where ray is parallel to x or y axis
	if (cos(dir) == 0 || sin(dir) == 0)
		return (advance_parallel_ray(ray, dir));
	//calculate next entire x
	x_dir = sign(cos(dir));
	if (x_dir > 0)
		next_x.x = ceil(ray->x);
	else
		next_x.x = floor(ray->x) -1;
	if (next_x.x == ray->x)
		next_x.x += x_dir;
	next_x.y = slope * next_x.x + offset;
	//calculate next entire y
	y_dir = sign(sin(dir));
		if (y_dir > 0)
			next_y.y = ceil(ray->y);
		else
			next_y.y = floor(ray->y) -1;
		if (next_y.y == ray->y)
			next_y.y += y_dir;
		next_y.x = (next_y.y - offset) / slope;
	//compare len (from ray)
	if (get_point_dist(*ray, next_x) < get_point_dist(*ray, next_y))
		*ray = next_x;
	else
		*ray = next_y;
}

void    get_first_pos(t_coord *ray, double dir, double slope, double offset)
{
	t_coord	tmp;

	//secu : simplificate dir it's now between -pi and pi;
	dir = simplificate_angle(dir);
	//exception : if x or y is entire
		//special case
	//determine sector, set corresponding var :
	if (dir >= -M_PI/4 && dir <= M_PI/4)
		tmp.x = ceil(ray->x);
	else if ((dir >= 3*M_PI/4 && dir <= M_PI) || (dir <= -3 * M_PI/4 && dir <= -M_PI))
		tmp.x = floor(ray->x);
	else if (dir >= M_PI/4 && dir <= 3 * M_PI/4)
		tmp.y = ceil(ray->y);
	else if (dir >= -3 * M_PI/4 && dir <= -M_PI/4)
		tmp.y = floor(ray->y);
	else
		ft_error("no quarter fit this angle", ERR_WTF);
	if (fabs(cos(dir)) >= fabs(sin(dir)))
		tmp.y = slope * tmp.x + offset;
	else
		tmp.x = (tmp.y - offset) / slope;
	
	*ray = tmp;
}
