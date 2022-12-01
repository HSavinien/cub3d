/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:41:22 by cmaroude          #+#    #+#             */
/*   Updated: 2022/12/01 17:15:38 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "chloutils.h"

// look like a placeholder, I leave it here until confirmation...
void	init_window_images(t_mlx *mlx)
{
	/* window */
//	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	/* image principal */
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
		&mlx->img.size_l, &mlx->img.endian);
}

void	init_minimap(t_mlx *mlx)
{
	/* image */
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr,
		&mlx->minimap.bpp, &mlx->minimap.size_l, &mlx->minimap.endian);
}
void	init_background(t_mlx *mlx)
{
	int		count_w;
	int		count_h;

	count_h = -1;
	while (++count_h < WIN_HEIGHT)
	{
		count_w = -1;
		while (++count_w < WIN_WIDTH)
		{
			if (count_h > WIN_HEIGHT / 2)
				mlx->img.data[TO_COORD(count_w, count_h)] = 0x993300;//mlx->map_s->roof_color;
			else
				mlx->img.data[TO_COORD(count_w, count_h)] = 0x33CCFF;//mlx->map_s->floor_color;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
