/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chloutils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:17:42 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/01 17:21:53 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHLOUTILS_H
# define CHLOUTILS_H
#include "cub3d.h"

# define TO_COORDMM(X,Y) ((int)floor(Y) * IMG_WIDTH + (int)floor(X))
# define TO_COORD(X,Y) ((int)floor(Y) * WIN_WIDTH + (int)floor(X))

# define TSIZE 32
# define TILE_SMM 8
# define WIN_WIDTH 15 * TSIZE
# define WIN_HEIGHT 11 * TSIZE
# define IMG_WIDTH 15 * TILE_SMM
# define IMG_HEIGHT 11 * TILE_SMM

/* draw_minimap.c */
void	draw_minimap(t_mlx *mlx);

/* loop.c */
int		loop(t_mlx *mlx);

/* init_images.c */
void	init_window_images(t_mlx *mlx);
void	init_background(t_mlx *mlx);
void	init_minimap(t_mlx *mlx);

/* hook.c */
int		close_win(t_mlx *mlx);
int		event_hook(int key, t_mlx *mlx);

#endif
