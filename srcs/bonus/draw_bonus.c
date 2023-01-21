/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:50:51 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/21 15:09:21 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minimap.h>

/* image */
void	init_minimap(t_mlx *mlx)
{
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, MM_W * TILE_SMM,
			MM_H * TILE_SMM);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr,
			&mlx->minimap.bpp, &mlx->minimap.size_l, &mlx->minimap.endian);
}

void	draw_crosshair(t_mlx *mlx)
{
	t_img	cross;

	cross = mlx->sprites->crosshair;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, cross.img_ptr,
		WIN_W / 2 - cross.width / 2, WIN_H / 2 - cross.height / 2);
}

void	put_compass(t_mlx *mlx)
{
	t_img	*compass;

	compass = &mlx->sprites->compass;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, compass->img_ptr, 
		30, WIN_H - compass->height - 30);
}

void	draw_bonus(t_mlx *mlx)
{	
	init_minimap(mlx);
	draw_minimap(mlx);
	put_compass(mlx);
	draw_crosshair(mlx);
}
