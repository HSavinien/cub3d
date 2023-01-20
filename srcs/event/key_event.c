/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:22:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 15:46:58 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (key == MOUSE_TGLE)
		toogle_mouse(mlx);
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
		;
	(void) mlx;
	return (0);
}

int	mouse_move(int mouse_x, int mouse_y, t_mlx *mlx)
{
	(void) mouse_y;
	if (mouse_x > WIN_W / 2)
		do_rotate(mlx, 1);
	if (mouse_x < WIN_W / 2)
		do_rotate(mlx, -1);
	mlx_mouse_move(mlx->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}
