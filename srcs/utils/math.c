/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:24:26 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/10 20:11:59 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	sign(double nb)
{
	if (nb < 0)
		return (-1);
	else
		return (1);
}

double get_point_dist(t_coord a, t_coord b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

/* function that calculate the equivalent angle, bound between 0 and 2pi,
 * of any angle, positive or negative.
 */

double simplify_angle_full(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}


double simplify_angle_half(double angle)
{
	while (angle < -M_PI)
		angle += 2 * M_PI;
	while (angle >= M_PI)
		angle -= 2 * M_PI;
	return (angle);
}	

/* function that calculate the angle between two lines.
 * the two lines are defined by their respective angle with the X axis.
 */
double	get_line_angle(double side1, double side2)
{
	double diff;

	side1 = simplify_angle_half(side1);
	side2 = simplify_angle_half(side2);
	diff = fabs(side1 - side2);
    return (fmin(diff, 2*M_PI - diff));
}
