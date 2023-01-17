/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:21:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/17 11:09:49 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <movement.h>

/* image */
void	init_minimap(t_mlx *mlx)
{
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, MM_W * TILE_SMM,
		MM_H * TILE_SMM);
	//printf("%d; %d\n", mlx->map_s->nb_column, mlx->map_s->nb_line);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr,
			&mlx->minimap.bpp, &mlx->minimap.size_l, &mlx->minimap.endian);
}

void	do_tile_conv(t_point *pt)
{
	pt->x *= TILE_SMM;
	pt->y *= TILE_SMM;
}
