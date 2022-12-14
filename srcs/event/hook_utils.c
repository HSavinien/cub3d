/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:58:00 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/18 14:09:43 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

t_vector	init_data_dir(t_mlx *mlx)
{
	t_vector	vec_dir;

	vec_dir.pos = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	vec_dir.dir = (t_point){(cos(mlx->player.direction) + vec_dir.pos.x),
		(sin(mlx->player.direction) + vec_dir.pos.y)};
	return (vec_dir);
}

double	rad_to_degree(double rad)
{
	double	dir_deg;

	dir_deg = rad * (180.0 / M_PI);
	dir_deg = dir_deg - 360.0 * floor(dir_deg / 360.0);
	return (dir_deg);
}
