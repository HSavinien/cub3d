/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:22:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/19 14:00:00 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

int	keypress(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_win(mlx);
	if (key == MOVE_FORWARD)
		mlx->key.forwd = 1;
	if (key == MOVE_BACKWARD)
		mlx->key.backwd = 1;
	if (key == MOVE_LEFT)
		mlx->key.left = 1;
	if (key == MOVE_RIGHT)
		mlx->key.right = 1;
	if (key == TURN_LEFT)
		mlx->key.rot_left = 1;
	if (key == TURN_RIGHT)
		mlx->key.rot_right = 1;
	if (key == ACT_KEY)
		toogle_door(mlx);
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == MOVE_FORWARD)
		mlx->key.forwd = 0;
	if (key == MOVE_BACKWARD)
		mlx->key.backwd = 0;
	if (key == MOVE_LEFT)
		mlx->key.left = 0;
	if (key == MOVE_RIGHT)
		mlx->key.right = 0;
	if (key == TURN_LEFT)
		mlx->key.rot_left = 0;
	if (key == TURN_RIGHT)
		mlx->key.rot_right = 0;
	return (0);
}

int	mouse_press(int key, t_mlx *mlx)
{
	if (key == MOUSE_LMB)
		;//do_shoot(mlx);
	(void) mlx;
	return (0);
}

int	mouse_move(int mouse_x, int mouse_y, t_mlx *mlx)
{
	int dist;

	(void) mouse_y;
	mlx->key.turn = 0;
	if (mlx->key.pos_x == 0)
		mlx->key.pos_x = mouse_x;
	dist = 0;
	if (mouse_x > mlx->key.pos_x || mouse_x < mlx->key.pos_x)
	{	
		dist = mouse_x - mlx->key.pos_x;
		if (mouse_x < mlx->key.pos_x)
		dist = (mlx->key.pos_x - mouse_x) * (-1);
	}
	if (mlx->key.dist != dist)
		mlx->key.turn = 1;
	mlx->key.dist = dist;
	mlx->key.pos_x = mouse_x;
	return (0);
}
