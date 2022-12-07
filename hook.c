/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/06 18:36:14 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "chloutils.h"

int		close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

bool	do_move(t_point *pos, t_point dir, t_mlx *mlx)
{
	bool wall;

	wall = true;
	(void)mlx;
	printf("pos_x: %f, pos_y: %f\ndir_x: %f, dir_y: %f\n", pos->x, pos->y, dir.x, dir.y);
	printf("pos_x - dir_x: %f\npos_y - dir_y: %f\n", fabs(pos->x - dir.x), fabs(pos->y - dir.y));
	if (wall == true)
		return (false);
	return (true);
}

int		event_hook(int key, t_mlx *mlx)
{
	t_point	pos;
	t_point	dir;
	bool	move;
	double	dir_deg;

	pos = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	dir = (t_point){(cos(mlx->player.direction) + pos.x),
	   	(sin(mlx->player.direction) + pos.y)};
	dir_deg = mlx->player.direction * (180.0 / M_PI);
	dir_deg = dir_deg - 360.0 * floor(dir_deg / 360.0);
	move = true;
	if (key == KEY_ESC)
		close_win(mlx);
	if (key == MOVE_FORWARD && mlx->map_s->parsed_map[(int)pos.y - (1 * SPEED)][(int)pos.x] != 1)
	{	
		pos.y -= (SPEED * 1.0);
		move = do_move(&pos, dir, mlx);
	}
	if (key == MOVE_BACKWARD && mlx->map_s->parsed_map[(int)pos.y + (1 * SPEED)][(int)pos.x] != 1)
		pos.y += (SPEED * 1.0);
	if (key == MOVE_LEFT && mlx->map_s->parsed_map[(int)pos.y][(int)pos.x - (1 * SPEED)] != 1)
		pos.x -= (SPEED * 1.0);
	if (key == MOVE_RIGHT && mlx->map_s->parsed_map[(int)pos.y][(int)pos.x + (1 * SPEED)] != 1)
		pos.x += (SPEED * 1.0);
	if (key == TURN_RIGHT)
	{
		dir_deg = (dir_deg + 1.0);
		printf("dir: %f\n", dir_deg);
	}
	if (key == TURN_LEFT)
	{	
		dir_deg = (dir_deg - 1.0);
		printf("dir: %f\n", dir_deg);
	}
	if (move == true)
	{
		mlx->player.pos_x = pos.x;
		mlx->player.pos_y = pos.y;
	}
	mlx->player.direction = dir_deg * (M_PI / 180.0);
	//draw_filledcircle(&mlx->minimap, dirx * 8, diry * 8);
	return (0);
}
