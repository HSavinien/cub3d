/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:46:36 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/22 16:50:45 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub33d.h"

int		loop(t_mlx *mlx)
{
	init_minimap(mlx);
	draw_minimap(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->minimap.img_ptr);
	mlx->minimap.img_ptr = NULL;
	return (0);
}
