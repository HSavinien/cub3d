/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/24 00:27:07 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_win(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit (0);
}

int		event_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
//		close_win(mlx);
		exit(0); //close window alone will cause segfault
	return (0);
	(void) mlx;
}
