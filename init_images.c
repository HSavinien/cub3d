/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:41:22 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/22 16:50:26 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window_and_image(t_mlx *mlx)
{
	/* window */
	mlx->mlx_ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
}

void	init_minimap(t_mlx *mlx)
{
	/* image */
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr, &mlx->minimap.bpp, &mlx->minimap.size_l,	&mlx->minimap.endian);
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
				mlx->img.data[count_h * WIN_WIDTH + count_w] = 0x993300;
			else
				mlx->img.data[count_h * WIN_WIDTH + count_w] = 0x33CCFF;
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}
