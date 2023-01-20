/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:27:52 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 15:29:04 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"
# include <stdbool.h>

# define TSIZE 32
# define TILE_SMM 8
# define MM_W 20
# define MM_H 20

/* draw_minimap.c */
void	draw_minimap(t_mlx *mlx);
void	draw_filledcircle(t_mlx *mlx, t_coord pl, int r);
void	draw_rev_circle(t_mlx *mlx, double x, double y, int r);
void	draw_line(t_mlx *mlx, t_coord dir, t_coord player);
void	draw_square(t_mlx *mlx, int x, int y, int color);

/* minimap_utils.c */
void	do_tile_conv(t_coord *pt);
t_coord	init_delta(t_coord player, t_coord dir);
void	add_delta(t_coord *player, t_coord *player_org, t_coord delta);
int		get_offset(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m);
int		map_line(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m, bool end);

#endif
