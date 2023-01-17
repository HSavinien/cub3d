/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:22:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/17 13:20:29 by cmaroude         ###   ########.fr       */
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
