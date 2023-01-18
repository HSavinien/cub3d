/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:20:50 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/18 17:39:14 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <movement.h>

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	x *= TILE_SMM;
	y *= TILE_SMM;
	i = 0;
	while (i < TILE_SMM)
	{
		j = 0;
		while (j < TILE_SMM)
		{
			mlx->minimap.data[((int)(x) + i) * MM_W * TILE_SMM
				+ (int)(j + y)] = color;
			j++;
		}
		i++;
	}
}

void	draw_filledcircle(t_mlx *mlx, double x, double y)
{
	int		i;
	int		r2;
	int		rr;
	double	tx;
	double	ty;

	r2 = pow((TILE_SMM / 2), 2);
	rr = (TILE_SMM / 2) << 1;
	i = 0;
	while (i < (r2 << 2))
	{
		tx = (i % rr) - (TILE_SMM / 2);
		ty = (i / rr) - (TILE_SMM / 2);
		if (tx * tx + ty * ty <= (rr + rr))
		{	
			if ((int)(x * TILE_SMM) < (MM_W * TILE_SMM) &&
				(int)(y * TILE_SMM) < (MM_H * TILE_SMM))
			{
				mlx->minimap.data[(int)(ty + (y * TILE_SMM)) *(MM_W * TILE_SMM)
					+ (int)(tx + (x * TILE_SMM))] = 0xFF0000;
			}
		}
		i++ ;
	}
}

void	draw_line(t_mlx *mlx, t_point dir, t_point player)
{
	t_point	delta;
	t_point	player_org;
	int		img_width;

	player_org = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	do_tile_conv(&player_org);
	img_width = MM_W * TILE_SMM;
	delta = init_delta(player, dir);
	while ((player.x < img_width && player.y < MM_H * TILE_SMM
			&& player.x > 0.0 && player.y > 0.0))
	{
		if (mlx->map_s->raw_map[(int)player_org.y / TILE_SMM]
			[(int)player_org.x / TILE_SMM] == '1')
			break ;
		mlx->minimap.data[(int)player.y * img_width + (int)player.x] = 0xFF00FF;
		add_delta(&player, &player_org, delta);
	}
}

void	draw_figures(t_mlx *mlx, t_pt_map mini_p, t_pt_map raw)
{
	t_point	dir_pt;
	t_point	player;

	player.x = mlx->player.pos_x - (raw.j - mini_p.j);
	player.y = mlx->player.pos_y - (raw.i - mini_p.i);
	dir_pt.x = (cos(mlx->player.direction) + player.x);
	dir_pt.y = (sin(mlx->player.direction) + player.y);
	if (mlx->map_s->raw_map[raw.i][raw.j] == '1')
		draw_square(mlx, mini_p.i, mini_p.j, 0xFFFFFF);
	else if (mlx->map_s->raw_map[raw.i][raw.j] == '0')
		draw_square(mlx, mini_p.i, mini_p.j, 0x80000000);
	draw_filledcircle(mlx, player.x, player.y);
	do_tile_conv(&dir_pt);
	do_tile_conv(&player);
	draw_line(mlx, dir_pt, player);
}

void	draw_minimap(t_mlx *mlx)
{
	t_pt_map	mini_m;
	t_pt_map	raw_p;
	bool		end;
	int			tmp_i;

	mini_m = (t_pt_map){0, 0};
	raw_p = (t_pt_map){0, 0};
	tmp_i = init_offset(mlx, &raw_p, &mini_m);
	mini_m.i += tmp_i - 1;
	while (mini_m.i < MM_H)
	{
		mini_m.j = 0;
		end = false;
		while (mini_m.j < MM_W)
		{
			end = map_line(mlx, &raw_p, &mini_m, end);
			mini_m.j++;
		}
		mini_m.i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		5 * TILE_SMM, ((WIN_H - ((MM_H + 5) * TILE_SMM))));
}
