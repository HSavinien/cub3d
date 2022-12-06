/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/06 16:11:22 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "chloutils.h"

int		close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

int		event_hook(int key, t_mlx *mlx)
{
	double	x;
	double	y;
	double	dir;
	double	dirx;
	double	diry;

	x = mlx->player.pos_x;
	y = mlx->player.pos_y;
	dirx = cos(mlx->player.direction);
	diry = sin(mlx->player.direction);
	dir = mlx->player.direction * (180.0 / M_PI);
	dir = dir - 360.0 * floor(dir / 360.0);
	if (key == KEY_ESC)
		close_win(mlx);
	if (key == MOVE_FORWARD && mlx->map_s->parsed_map[(int)y - (1 * SPEED)][(int)x] != 1)
	{	
		y -= (SPEED * 1.0);
		//x += (dirx * SPEED);
		//y += (diry * SPEED);
	}
	if (key == MOVE_BACKWARD && mlx->map_s->parsed_map[(int)y + (1 * SPEED)][(int)x] != 1)
		y += (SPEED * 1.0);
	if (key == MOVE_LEFT && mlx->map_s->parsed_map[(int)y][(int)x - (1 * SPEED)] != 1)
		x -= (SPEED * 1.0);
	if (key == MOVE_RIGHT && mlx->map_s->parsed_map[(int)y][(int)x + (1 * SPEED)] != 1)
		x += (SPEED * 1.0);
	if (key == TURN_RIGHT)
	{
		dir = (dir + 1.0);
	}
	if (key == TURN_LEFT)
	{	
		dir = (dir - 1.0);
	}
	mlx->player.pos_x = x;
	mlx->player.pos_y = y;
	mlx->player.direction = dir * (M_PI / 180.0);
	//draw_filledcircle(&mlx->minimap, dirx * 8, diry * 8);
	return (0);
}
