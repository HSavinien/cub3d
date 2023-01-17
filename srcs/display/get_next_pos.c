/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:48:15 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/03 21:18:57 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

double	calculate_next_int(double start, double dir)
{
	if (start == floor(start))
	{
		if (dir > 0)
			return (ceil(start) + 1);
		else
			return (floor(start) -1);
	}
	else if (dir > 0)
		return (ceil(start));
	else
		return (floor(start));
	

}

// cos and sin are called often in function and subfunction.
// store them in t_coord to optimise
void    get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	t_coord	next_x;
	t_coord	next_y;
	
	//check case where ray is parallel to x or y axis
	if (cos(dir) == 0 || sin(dir) == 0)
		return (advance_parallel_ray(ray, dir));
	//calculate next entire x
	next_x.x = calculate_next_int(ray->x, cos(dir));
	next_x.y = slope * next_x.x + offset;
	//calculate next entire y
		next_y.y = calculate_next_int(ray->y, sin(dir));
		next_y.x = (next_y.y - offset) / slope;
	//compare len (from ray)
	if (get_point_dist(*ray, next_x) < get_point_dist(*ray, next_y))
		*ray = next_x;
	else
		*ray = next_y;
}
