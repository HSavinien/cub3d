/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:20:50 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/19 17:09:59 by cmaroude         ###   ########.fr       */
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
	while (i < (TILE_SMM))
	{
		j = 0;
		while (j < (TILE_SMM))
		{
			mlx->minimap.data[((int)(x) + i) * mlx->map_s->nb_column * TILE_SMM
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
			if ((int)(x * TILE_SMM) < mlx->map_s->nb_column * TILE_SMM &&
				(int)(y * TILE_SMM) < mlx->map_s->nb_line * TILE_SMM)
			{
				mlx->minimap.data[(int)(ty + (y * TILE_SMM))*(mlx->map_s->nb_column 
						* TILE_SMM) + (int)(tx + (x * TILE_SMM))] = 0xFF0000;
			}
		}
		i++ ;
	}
}

void	draw_line(t_mlx *mlx, t_point player, t_point dir)
{
	t_point	delta;
	int	img_width;
	double	step;

	img_width = mlx->map_s->nb_column * TILE_SMM;
	delta.x = dir.x - player.x;
	delta.y = dir.y - player.y;
	if (fabs(delta.x) > fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	while ((player.x < img_width && player.y < mlx->map_s->nb_line * TILE_SMM
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

void	draw_figures(t_mlx *mlx, int i, int j)
{
	t_point	dir_pt;
	t_point	player;

	dir_pt.x = (cos(mlx->player.direction)) + mlx->player.pos_x;
	dir_pt.y = (sin(mlx->player.direction)) + mlx->player.pos_y;
	player = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	if (mlx->map_s->raw_map[i][j] == '1')
		draw_square(mlx, i, j, 0xFFFFFF);
	else if (mlx->map_s->raw_map[i][j] == '0')
		draw_square(mlx, i, j, 0);
	draw_filledcircle(mlx, player.x, player.y);
	do_tile_conv(&dir_pt);
	do_tile_conv(&player);
	draw_line(mlx, player, dir_pt);
}

void	draw_minimap(t_mlx *mlx)
{
	int		i;
	int		j;
	bool	end;

	i = 0;
	while (i < mlx->map_s->nb_line)
	{
		j = 0;
		end = false;
		while (j < mlx->map_s->nb_column)
		{
			draw_square(mlx, i, j, 0x80000000);
			if (end == false && mlx->map_s->raw_map[i][j] != '\0')
				draw_figures(mlx, i, j);
			else
				end = true;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		0, ((WIN_H - (mlx->map_s->nb_line * TILE_SMM))));
}
