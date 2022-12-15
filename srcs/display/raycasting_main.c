/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/15 16:36:48 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that return an array of WIN_W double.
 * each value in the array represent the angle of the coresponding ray to cast.
 */
double	*get_ray_angle(t_mlx *mlx, double **angles)
{
	double	angles[WIN_W];//maloc instead, as it will be returned
	int		i;
	double	step;

	//get min and max angle
	angles[0] = mlx->player->direction - (FOV/2);
	angles[WIN_W -1] = mlx->player->direction + (FOV/2);
	//calculate interval between each angle (max-min + fov)
	//iterate through the range and get each ray
}

void	cast_ray(double angle, t_img *screen, t_mlx *mlx)
{
	double	dir;
	double	offset;
	double	pos;
	//get ray_equation
	dir = ;
	offset = ;
	pos = ;
	//cast ray
	//use trigo/pythagore to calculate 'straight' distance (anti fish eye)
	//calculate wall height
	//look wall direction
	//debug : fill pixel column with sigle colored pixel to see if it work
	//calculate pixel column based on image, and put it in image
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];	//list the angle of each ray, in rad


	//calculate the angle of each ray
	get_ray_angle(mlx, &ray_angle);
	i = 0;
	while (i < WIN_W)
		cast_ray(ray_angles[i ++], screen, mlx);
}
