/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/17 15:11:48 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "chloutils.h"

int		close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

t_vector	init_data_dir(t_mlx *mlx)
{
	t_vector	vec_dir;
	
	vec_dir.pos = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	vec_dir.dir = (t_point){(cos(mlx->player.direction) + vec_dir.pos.x),
	   	(sin(mlx->player.direction) + vec_dir.pos.y)};
	return (vec_dir);
}

double	dir_move(int key)
{
	if ((key == MOVE_BACKWARD) || (key == MOVE_LEFT))
		return (-1.0);
	else
		return (1.0);
}

int		do_move(int key, t_mlx *mlx)
{
	t_vector	vec_dir; //vecteur du direction du regard
	t_point		pos_tmp;
	t_point		vect;
	double		dir;
	
	vec_dir = init_data_dir(mlx);
	dir = dir_move(key);
	if ((key == MOVE_LEFT) || (key == MOVE_RIGHT))
	{
		vec_dir.dir.x = (cos(mlx->player.direction + M_PI_2) + vec_dir.pos.x);
	   	vec_dir.dir.y = (sin(mlx->player.direction + M_PI_2) + vec_dir.pos.y);
	}
	vect = (t_point){(vec_dir.dir.x - vec_dir.pos.x) * dir,
			(vec_dir.dir.y - vec_dir.pos.y) * dir};
	pos_tmp.x = (vect.x * SPEED) + vec_dir.pos.x;
	pos_tmp.y = (vect.y * SPEED) + vec_dir.pos.y;
	if (mlx->map_s->parsed_map[(int)pos_tmp.y][(int)pos_tmp.x] ==  1)
		return (1);
	mlx->player.pos_x = pos_tmp.x;
	mlx->player.pos_y = pos_tmp.y;
	return (0);
}

double rad_to_deg(double rad)
{
	double	dir_deg;

	dir_deg = rad * (180.0 / M_PI);
	dir_deg = dir_deg - 360.0 * floor(dir_deg / 360.0);
	return (dir_deg);
}

void	do_turn(int key, double *deg)
{
	double turn;

	turn = 5.0;
	if (key == TURN_LEFT)
		turn *= -1.0;
	*deg = (*deg + turn);
}

int		event_hook(int key, t_mlx *mlx)
{
	double	dir_deg;

	dir_deg = rad_to_deg(mlx->player.direction);
	if (key == KEY_ESC)
		close_win(mlx);
	if ((key == MOVE_FORWARD) || (key == MOVE_BACKWARD) || (key == MOVE_LEFT) ||
			(key == MOVE_RIGHT))
		do_move(key, mlx);
	if (key == TURN_RIGHT)
		dir_deg = (dir_deg + 1.0);
	if (key == TURN_LEFT)
		dir_deg = (dir_deg - 1.0);
	mlx->player.direction = dir_deg * (M_PI / 180.0);
	return (0);
}
