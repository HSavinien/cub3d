/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:48:15 by tmongell          #+#    #+#             */
/*   Updated: 2023/03/11 01:55:44 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	calculate_next_int(double start, double dir)
{
	if (start == floor(start))
	{
		if (dir > 0)
			return (ceil(start) + 1);
		else
			return (floor(start) - 1);
	}
	else if (dir > 0)
		return (ceil(start));
	else
		return (floor(start));
}

// cos and sin are called often in function and subfunction.
// store them in t_coord to optimise
void	get_next_pos(t_coord *ray, double dir, double slope, double offset)
{
	t_coord	next_x;
	t_coord	next_y;

	next_x.x = calculate_next_int(ray->x, cos(dir));
	next_x.y = slope * next_x.x + offset;
		next_y.y = calculate_next_int(ray->y, sin(dir));
		next_y.x = (next_y.y - offset) / slope;
	if (get_point_dist(*ray, next_x) < get_point_dist(*ray, next_y))
		*ray = next_x;
	else
		*ray = next_y;
}
