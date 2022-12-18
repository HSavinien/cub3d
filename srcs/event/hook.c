/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/18 15:03:45 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

double	dir_move(int key)
{
	if ((key == MOVE_BACKWARD) || (key == MOVE_LEFT))
		return (-1.0);
	else
		return (1.0);
}

int	do_move(int key, t_mlx *mlx)
{
	t_vector	v_dir;
	t_point		pos_tmp;
	t_point		vect;
	double		dir;

	v_dir = init_data_dir(mlx);
	dir = dir_move(key);
	if ((key == MOVE_LEFT) || (key == MOVE_RIGHT))
	{
		v_dir.dir.x = (cos(mlx->player.direction + M_PI_2) / 2 + v_dir.pos.x);
		v_dir.dir.y = (sin(mlx->player.direction + M_PI_2) / 2 + v_dir.pos.y);
	}
	vect = (t_point){(v_dir.dir.x - v_dir.pos.x) * dir,
		(v_dir.dir.y - v_dir.pos.y) * dir};
	pos_tmp.x = (vect.x * SPEED) + v_dir.pos.x;
	pos_tmp.y = (vect.y * SPEED) + v_dir.pos.y;
	if (mlx->map_s->parsed_map[(int)pos_tmp.y][(int)pos_tmp.x] == 1)
		return (1);
	mlx->player.pos_x = pos_tmp.x;
	mlx->player.pos_y = pos_tmp.y;
	return (0);
}

int	event_hook(int key, t_mlx *mlx)
{
	double	dir_deg;

	dir_deg = rad_to_degree(mlx->player.direction);
	if (key == KEY_ESC)
		close_win(mlx);
	if ((key == MOVE_FORWARD) || (key == MOVE_BACKWARD) || (key == MOVE_LEFT)
		|| (key == MOVE_RIGHT))
		do_move(key, mlx);
	if (key == TURN_RIGHT)
		dir_deg = (dir_deg + 1.0);
	if (key == TURN_LEFT)
		dir_deg = (dir_deg - 1.0);
	mlx->player.direction = dir_deg * (M_PI / 180.0);
	return (0);
}
