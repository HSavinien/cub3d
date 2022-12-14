/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:17:42 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/19 17:11:38 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include <cub3d.h>
# include <stdbool.h>

# define TSIZE 32
# define TILE_SMM 8

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

/* minimap_utils.c */
void		init_minimap(t_mlx *mlx);
void		do_tile_conv(t_point *pt);

/* loop.c */
int			loop(t_mlx *mlx);

/* init_images.c */
void		init_window_images(t_mlx *mlx);
void		init_background(t_mlx *mlx);
void		init_minimap(t_mlx *mlx);

/* hook.c */
int			close_win(t_mlx *mlx);
int			event_hook(int key, t_mlx *mlx);

/* hook_utils */
t_vector	init_data_dir(t_mlx *mlx);
double		rad_to_degree(double rad);

#endif
