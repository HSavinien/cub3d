/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_toogle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 00:12:24 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/20 17:58:07 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_door(char c)
{
	return (c == DOOR_OP || c == DOOR_CL);
}

void	activate_door(int y, int x, t_map *map_s)
{
	if (map_s->parsed_map[x][y] == DOOR_CL)
		map_s->parsed_map[x][y] = DOOR_OP;
	else if (map_s->parsed_map[x][y] == DOOR_OP)
		map_s->parsed_map[x][y] = DOOR_CL;
}

void	toogle_door(t_mlx *mlx_s)
{
	t_coord		pos;
	double		dir;

	pos = (t_coord){mlx_s->player.pos_x, mlx_s->player.pos_y};
	dir = simplify_angle_half(mlx_s->player.direction);
	if (dir >= 0)
	{
		if (dir < M_PI_4)
			activate_door(pos.x + 1, pos.y, mlx_s->map_s);
		else if (dir < 3 * M_PI_4)
			activate_door(pos.x, pos.y + 1, mlx_s->map_s);
		else
			activate_door(pos.x - 1, pos.y, mlx_s->map_s);
	}
	else
	{
		if (dir > -M_PI_4)
			activate_door(pos.x + 1, pos.y, mlx_s->map_s);
		else if (dir > -3 * M_PI_4)
			activate_door(pos.x, pos.y - 1, mlx_s->map_s);
		else
			activate_door(pos.x - 1, pos.y, mlx_s->map_s);
	}
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
