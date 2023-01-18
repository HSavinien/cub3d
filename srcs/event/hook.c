/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/18 20:33:04 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

double	dir_move(t_mlx *mlx, int l)
{
	if (mlx->key.left == 1 && l == 1)
		return (-1.0);
	if (mlx->key.backwd == 1 && l == 0)
		return (-1.0);
	else
		return (1.0);
}

int	verif_pos(double x, double y, t_mlx *mlx, double buf)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = x + buf;
	tmp_y = y + buf;
	if (mlx->map_s->parsed_map[(int)y][tmp_x] == 1)
		return (1);
	if (mlx->map_s->parsed_map[tmp_y][(int)x] == 1)
		return (1);
	if (mlx->map_s->parsed_map[tmp_y][tmp_x] == 1)
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

int	do_move(t_mlx *mlx, int l)
{
	t_vector	vdir;
	t_point		pos_tmp;
	t_point		vect;
	double		dir;
	double		speed;

	speed = SPEED * 5;
	vdir = init_data_dir(mlx);
	dir = dir_move(mlx, l);
	if (l == 1)
	{
		vdir.dir.x = (cos(mlx->player.direction + M_PI_2) * speed + vdir.pos.x);
		vdir.dir.y = (sin(mlx->player.direction + M_PI_2) * speed + vdir.pos.y);
	}
	vect = (t_point){(vdir.dir.x - vdir.pos.x) * dir,
		(vdir.dir.y - vdir.pos.y) * dir};
	pos_tmp.x = (vect.x * SPEED) + vdir.pos.x;
	pos_tmp.y = (vect.y * SPEED) + vdir.pos.y;
	if (verif_col(pos_tmp.x, pos_tmp.y, mlx))
		return (1);
	mlx->player.pos_x = pos_tmp.x;
	mlx->player.pos_y = pos_tmp.y;
	return (0);
}

int	event_hook(t_mlx *mlx)
{
	if ((mlx->key.forwd || mlx->key.backwd)
		&& !(mlx->key.forwd && mlx->key.backwd))
		do_move(mlx, 0);
	if ((mlx->key.left || mlx->key.right) && !(mlx->key.left && mlx->key.right))
		do_move(mlx, 1);
	if (!(mlx->key.rot_left && mlx->key.rot_right))
	{
		if (mlx->key.rot_right)
			mlx->player.direction += 0.020;
		if (mlx->key.rot_left)
			mlx->player.direction -= 0.020;
	}
	return (0);
}
