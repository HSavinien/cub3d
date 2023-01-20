/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:22:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 13:46:51 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

int	close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

void	toogle_mouse(t_mlx *mlx_s)
{
	static char	mouse_active = 0;

	if (mouse_active)
	{
		mlx_mouse_show();
		mlx_hook(mlx_s->win_ptr, EVENT_MOTION, 0, NULL, mlx_s);
		mouse_active = 0;
	}
	else
	{
		mlx_mouse_hide();
		mlx_hook(mlx_s->win_ptr, EVENT_MOTION, 0, mouse_move, mlx_s);
		mouse_active = 1;
	}
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
		;//do_shoot(mlx);
	(void) mlx;
	return (0);
}

int	mouse_move(int mouse_x, int mouse_y, t_mlx *mlx)
{

	(void) mouse_y;
	if (mouse_x > WIN_W/2)
		do_rotate(mlx, 1);
	if (mouse_x < WIN_W/2)
			do_rotate(mlx, -1);
	mlx_mouse_move(mlx->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}
