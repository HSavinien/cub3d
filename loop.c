/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:46:36 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/24 00:28:28 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop(t_mlx *mlx)
{
	init_minimap(mlx);
//	draw_minimap(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->minimap.img_ptr);
	mlx->minimap.img_ptr = NULL;
	return (0);
}
