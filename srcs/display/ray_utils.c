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
//	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	data->distance = sqrt(pow(player->pos_x - ray.x, 2) +
		pow(player->pos_y - ray.y, 2));
	//little modif to avoid infinit height wall :
//	if (data->distance < 0.1)
//		data->distance = 0.1;
	data->side = face;
	data->pos=ray;
	return (1);
}

/*exception case of get_next_pos for when a ray is parrallel to an axis.
 */
void	advance_parallel_ray(t_coord *ray, double dir)
{
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	if (cos(dir) == 1)
	{
		if (ray->x == floor(ray->x))
			ray->x += 1;
		ray->x = ceil(ray->x);
	}
	else if (cos(dir) == -1)
	{
		if (ray->x == floor(ray->x))
			ray->x -= 1;
		ray->x = floor(ray->x);
	}
	else if (sin(dir) == 1)
	{
		if (ray->y == floor(ray->y))
			ray->y += 1;
		ray->y = ceil(ray->y);
	}
	else if (sin(dir) == -1)
	{
		if (ray->y == floor(ray->y))
			ray->y += 1;
		ray->y = ceil(ray->y);
	}
}
void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	//dprintf(2, "advancing ray [%f;%f] allong right y=%fx+%f, dir %f\n",//debug
//		ray->x, ray->y, slope, offset, dir);//DEBUG
	int	x_dir;
	int	y_dir;
	t_coord	tmp;
	//if cos or sin == 0, enter specific function
	if (cos(dir) == 0 || sin(dir) == 0)
		return (advance_parallel_ray(ray, dir));
	//dprintf(2, "ray is not parrallel to grid\n");//DEBUG
	//get x and y dir, (+-1, based on sin and cos);
	x_dir = sign(cos(dir));
	y_dir = sign(sin(dir));
	//dprintf(2, "got x_dir = %d, y_dir = %d\n", x_dir, y_dir);//DEBUG
	//get tmp coord to next entire x value, and corresponding y
	if (x_dir > 0)
		tmp.x = ceil(ray->x);
	else
		tmp.x = floor(ray->x) -1;
	tmp.y = slope * tmp.x + offset;
	//dprintf(2, "found tmp coord : %f, %f\n", tmp.x, tmp.y);//DEBUG
	//if entire part of tmp.y != entire part of ray.y, calculate next y
	if (floor(tmp.y) != floor(ray->y))
	{
		//dprintf(2, "y gone to far. recalculating tmp\n");//DEBUG
		if (y_dir > 0)
			tmp.y = ceil(ray->y);
		else
			tmp.y = floor(ray->y) -1;
		tmp.x = (tmp.y - offset) / slope;
		//dprintf(2, "found new tmp coord : %f, %f\n", tmp.x, tmp.y);//DEBUG
	}
	*ray = tmp;
	//dprintf(2, "updated ray : ray = [%f;%f], tmp = [%f;%f]\n",
//		ray->x, ray->y, tmp.x, tmp.y);//DEBUG
}
/* function that get the next entire x or y on the direction line */
/*
void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	double		step_x;
	double		step_y;
	//	y = slope * x + offset;
	//	from 180 include to 360 non include
	printf("fct:\nx: %f, y: %f, dir: %f, slope: %f, offset: %f\n", ray->x, ray->y, dir, slope, offset);
	step_x = fabs(ray->x - ceil(ray->x));
	if (step_x == 0.0)
		step_x = 1.0;
	// if dir = 0 for x
	if (fabs(dir - 0.0) <= EPS || fabs(dir - 2 * M_PI) <= EPS)
		ray->x = round(ray->x + step_x);
	// if dir = 180 for x
	else if (fabs(dir - M_PI) <= EPS)
		ray->x = round(ray->x - step_x);
	step_y = fabs(ray->y - ceil(ray->y));
	if (step_y == 0.0)
		step_y = 1.0;
	// if dir  = 90 for y
	if (fabs(dir - (M_PI / 2)) <= EPS)
		ray->y = round(ray->y - step_y);
	// if dir = 270 for y
	else if (fabs(dir - (3 * M_PI / 2)) <= EPS)
		ray->y = round(ray->y + step_y);
//	printf("fct:\nx: %f, y: %f, dir: %f, slope: %f, offset: %f, step_x: %f, step_y: %f\n", ray->x, ray->y, dir, slope, offset, step_x, step_y);
	if (step_y >= step_x && fabs(dir - 0.0) >= EPS && fabs(dir - 2 * M_PI) <= EPS && fabs(dir - M_PI) <= EPS && fabs(dir - (M_PI / 2)) <= EPS && fabs(dir - (3 * M_PI / 2)) <= EPS) 
	{
		printf("here 2\n");
		ray->x += step_x;
		ray->y = slope * round(ray->x) + offset;
	}
	else if (step_x > step_y && fabs(dir - 0.0) >= EPS && fabs(dir - 2 * M_PI) <= EPS && fabs(dir - M_PI) <= EPS && fabs(dir - (M_PI / 2)) <= EPS && fabs(dir - (3 * M_PI / 2)) <= EPS)
	{	
		printf("here 3\n");
		ray->y += step_y;
		ray->x = round(ray->y) - offset / slope;
	}
}
*/
