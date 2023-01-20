/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:20:50 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 19:24:13 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minimap.h>

void	draw_square(t_mlx *mlx, int y, int x, int color)
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
			if ((int)(x) + j < (MM_W * TILE_SMM) &&
				(int)(y) + i < (MM_H * TILE_SMM))
			{	
				mlx->minimap.data[((int)(y) + i) * MM_W * TILE_SMM
					+ (int)(x + j)] = color;
			}
			j++;
		}
		i++;
	}
}

void	draw_filledcircle(t_mlx *mlx, t_coord pl, int r)
{
	int		i;
	int		r2;
	int		rr;
	t_coord	t;

	r2 = pow(r, 2);
	rr = r << 1;
	i = 0;
	while (i < (r2 << 2))
	{
		t = (t_coord){(i % rr) - r, (i / rr) - r};
		if (t.x * t.x + t.y * t.y <= (rr + rr))
		{	
			if ((int)(pl.x) < (MM_W * TILE_SMM) &&
				(int)(pl.y) < (MM_H * TILE_SMM))
			{
				mlx->minimap.data[(int)(t.y + pl.y) *(MM_W * TILE_SMM)
					+ (int)(t.x + pl.x)] = 0xFF0000;
			}
		}
		i++ ;
	}
}

void	draw_line(t_mlx *mlx, t_coord dir, t_coord player)
{
	t_coord	delta;
	t_coord	player_org;
	bool	end;
	int		img_width;

	player_org = (t_coord){mlx->player.pos_x, mlx->player.pos_y};
	do_tile_conv(&player_org);
	img_width = MM_W * TILE_SMM;
	delta = init_delta(player, dir);
	while ((player.x < img_width && player.y < MM_H * TILE_SMM
			&& player.x > 0.0 && player.y > 0.0))
	{
		end = false;
		if (end == false && mlx->map_s->raw_map[(int)player_org.y / TILE_SMM]
			[(int)player_org.x / TILE_SMM] != '\0')
			;
		else
			end = true;
		if (end == true || verif_col(player_org.x / TILE_SMM,
				player_org.y / TILE_SMM, mlx))
			break ;
		mlx->minimap.data[(int)player.y * img_width + (int)player.x] = 0xFF00FF;
		add_delta(&player, &player_org, delta);
	}
}

void	draw_figures(t_mlx *mlx, t_pt_map mini_p, t_pt_map raw)
{
	t_coord	dir_pt;
	t_coord	player;

	player.x = mlx->player.pos_x - (raw.j - mini_p.j);
	player.y = mlx->player.pos_y - (raw.i - mini_p.i);
	dir_pt.x = (cos(mlx->player.direction) + player.x);
	dir_pt.y = (sin(mlx->player.direction) + player.y);
	if (mlx->map_s->raw_map[raw.i][raw.j] == '1')
		draw_square(mlx, mini_p.i, mini_p.j, 0xFFFFFF);
	else if (mlx->map_s->raw_map[raw.i][raw.j] == '0')
		draw_square(mlx, mini_p.i, mini_p.j, 0x80000000);
	else if (mlx->map_s->parsed_map[raw.i][raw.j] == DOOR_CL)
		draw_square(mlx, mini_p.i, mini_p.j, 0xFF);
	else if (mlx->map_s->parsed_map[raw.i][raw.j] == DOOR_OP)
		draw_square(mlx, mini_p.i, mini_p.j, 0x800000FF);
	do_tile_conv(&player);
	draw_filledcircle(mlx, player, (TILE_SMM / 2));
	do_tile_conv(&dir_pt);
	draw_line(mlx, dir_pt, player);
}

void	draw_minimap(t_mlx *mlx)
{
	t_coord		c;
	t_pt_map	mini_m;
	t_pt_map	raw_p;
	bool		end;
	t_pt_map	tmp;

	c = (t_coord){((MM_W / 2) * TILE_SMM), ((MM_H / 2) * TILE_SMM)};
	mini_m = (t_pt_map){0, 0};
	raw_p = (t_pt_map){0, 0};
	tmp = get_offset(mlx, &raw_p, &mini_m);
	mini_m.i += tmp.i - 1;
	while (mini_m.i < MM_H)
	{
		mini_m.j = -tmp.j - 1;
		end = false;
		while (++mini_m.j < MM_W)
			end = map_line(mlx, &raw_p, &mini_m, end);
		mini_m.i++;
	}
	draw_rev_circle(mlx, c.x, c.y, c.y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		5 * TILE_SMM, ((WIN_H - ((MM_H + 5) * TILE_SMM))));
}
