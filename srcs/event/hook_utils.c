/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:58:00 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 15:25:12 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	init_data_dir(t_mlx *mlx)
{
	t_vec	vec_dir;

	vec_dir.pos = (t_coord){mlx->player.pos_x, mlx->player.pos_y};
	vec_dir.dir = (t_coord){(cos(mlx->player.direction) + vec_dir.pos.x),
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
