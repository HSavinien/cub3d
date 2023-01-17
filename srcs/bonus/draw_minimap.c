/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:20:50 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/17 17:34:52 by cmaroude         ###   ########.fr       */
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
				mlx->minimap.data[(int)(ty + (y * TILE_SMM)) * (MM_W * TILE_SMM)
					+ (int)(tx + (x * TILE_SMM))] = 0xFF0000;
			}
		}
		i++ ;
	}
}

void	draw_line(t_mlx *mlx, t_point player, t_point dir)
{
	t_point	delta;
	int		img_width;
	double	step;

	img_width = MM_W * TILE_SMM;
	delta.x = dir.x - player.x;
	delta.y = dir.y - player.y;
	if (fabs(delta.x) > fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	while ((player.x < img_width && player.y < MM_H * TILE_SMM
			&& player.x > 0.0 && player.y > 0.0))
	{
		if (mlx->map_s->raw_map[(int)player.y / TILE_SMM]
			[(int)player.x / TILE_SMM] == '1')
			break ;
		mlx->minimap.data[(int)player.y * img_width + (int)player.x] = 0xFF00FF;
		player.x += delta.x;
		player.y += delta.y;
	}
}

void	draw_figures(t_mlx *mlx, t_point_map mini_p, t_point_map raw)
{
	t_point	dir_pt;
	t_point	player;

	player = (t_point){mlx->player.pos_x - (raw.j - mini_p.j), mlx->player.pos_y - (raw.i - mini_p.i)};
	dir_pt.x = (cos(mlx->player.direction)) + player.x;
	dir_pt.y = (sin(mlx->player.direction)) + player.y;
	//player = (t_point){MM_W / 2, MM_H / 2};
	if (mlx->map_s->raw_map[raw.i][raw.j] == '1')
		draw_square(mlx, mini_p.i, mini_p.j, 0xFFFFFF);
	else if (mlx->map_s->raw_map[raw.i][raw.j] == '0')
		draw_square(mlx, mini_p.i, mini_p.j, 0x80000000);
	//if (raw.i == (int)player.y && raw.j == (int)player.x)
		draw_filledcircle(mlx, player.x, player.y);
	do_tile_conv(&dir_pt);
	do_tile_conv(&player);
//	draw_line(mlx, player, dir_pt);
}

void	draw_minimap(t_mlx *mlx)
{
	t_point_map mini_m;
	t_point_map raw_p;
	t_point_map draw_p;
	bool	end;

	mini_m.i = 0;
	raw_p.i =  mlx->player.pos_y - (MM_H / 2);
	if (raw_p.i < 0)
		raw_p.i = 0;
	raw_p.j = mlx->player.pos_x - (MM_W / 2);
	if (raw_p.j < 0)
		raw_p.j = 0;
	while (mini_m.i < MM_H) //(i < mlx->map_s->nb_line)
	{
		mini_m.j = 0;
		end = false;
		draw_p.i = mini_m.i + raw_p.i;
		while (mini_m.j < MM_W) //(j < mlx->map_s->nb_column)
		{
			draw_p.i = mini_m.i + raw_p.i;
			draw_p.j = mini_m.j + raw_p.j;
			if ((draw_p.i) < mlx->map_s->nb_line && (draw_p.j) < mlx->map_s->nb_column 
				&& end == false && mlx->map_s->raw_map[draw_p.i][draw_p.j] != '\0') 
					draw_figures(mlx, mini_m, draw_p);
			else
				end = true;
			if (end == true && mini_m.j < MM_W)
				draw_square(mlx, mini_m.i, mini_m.j, 0x80000000);
			mini_m.j++;
		}
		mini_m.i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		5 * TILE_SMM, ((WIN_H - ((MM_H + 5) * TILE_SMM))));
}
