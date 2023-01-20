/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:09:46 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 15:15:16 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_pos(double x, double y, t_mlx *mlx, double buf)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = x + buf;
	tmp_y = y + buf;
	if (mlx->map_s->parsed_map[(int)y][tmp_x] & (WALL | DOOR_CL))
		return (1);
	if (mlx->map_s->parsed_map[tmp_y][(int)x] & (WALL | DOOR_CL))
		return (1);
	if (mlx->map_s->parsed_map[tmp_y][tmp_x] & (WALL | DOOR_CL))
		return (1);
	else
		return (0);
}

int	verif_col(double x, double y, t_mlx *mlx)
{
	double	buf;

	buf = 0.1;
	if (verif_pos(x, y, mlx, buf) == 1)
		return (1);
	buf = -0.1;
	if (verif_pos(x, y, mlx, buf) == 1)
		return (1);
	return (0);
}
