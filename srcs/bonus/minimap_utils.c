/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:21:40 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/19 17:39:08 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <movement.h>

/* image */
void	init_minimap(t_mlx *mlx)
{
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->map_s->nb_column
			* TILE_SMM, mlx->map_s->nb_line * TILE_SMM);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr,
			&mlx->minimap.bpp, &mlx->minimap.size_l, &mlx->minimap.endian);
}

void	do_tile_conv(t_point *pt)
{
	pt->x *= TILE_SMM;
	pt->y *= TILE_SMM;
}
