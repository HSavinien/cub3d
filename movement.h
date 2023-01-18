/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:17:42 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/18 17:31:58 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include <cub3d.h>
# include <stdbool.h>

# define TSIZE 32
# define TILE_SMM 8
# define MM_W 20
# define MM_H 20

/* structures */
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_vector
{
	t_point	pos;
	t_point	dir;
	t_point	len;
}	t_vector;

/* draw_minimap.c */
void		draw_minimap(t_mlx *mlx);
void		draw_filledcircle(t_mlx *mlx, double x, double y);
void		draw_line(t_mlx *mlx, t_point dir, t_point player);
void		draw_square(t_mlx *mlx, int x, int y, int color);

/* minimap_utils.c */
void		init_minimap(t_mlx *mlx);
void		do_tile_conv(t_point *pt);
t_point		init_delta(t_point player, t_point dir);
void		add_delta(t_point *player, t_point *player_org, t_point delta);
int			init_offset(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m);
int			map_line(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m, bool end);

/* loop.c */
int			loop(t_mlx *mlx);

/* init_images.c */
void		init_window_images(t_mlx *mlx);
void		init_background(t_mlx *mlx);
void		init_minimap(t_mlx *mlx);

/* hook.c */
int			event_hook(t_mlx *mlx);

/* hook_utils */
t_vector	init_data_dir(t_mlx *mlx);
double		rad_to_degree(double rad);

#endif
