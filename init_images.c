/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:41:22 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/23 12:12:27 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window_images(t_mlx *mlx)
{
	/* window */
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
}

void	init_minimap(t_mlx *mlx)
{
	/* image */
	mlx->minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx->minimap.data = (int *)mlx_get_data_addr(mlx->minimap.img_ptr, &mlx->minimap.bpp, &mlx->minimap.size_l,	&mlx->minimap.endian);
}

void	generate_noise(double *noise)
{
	int y;
	int x;
	
	y = 0;
	while (y++ < WIN_HEIGHT)
	{
		x = 0;
		while (x++ < WIN_WIDTH)
		{	
			noise[y * WIN_WIDTH + x] = (rand() % 32768) / 32768.0;
		}
	}
}

double	smooth_noise(double x, double y, double *noise)
{
	double	fractX;
	double	fractY;
	double	value;
	int		x1;
	int		x2;
	int		y1;
	int		y2;

	double	fractX = x - int(x);
	double	fractY = y - int(y);
	int x1 = (int(x) + WIN_WIDTH) % WIN_WIDTH;
	int y1 = (int(y) + WIN_HEIGHT) % WIN_HEIGHT;
	int x2 = (int(x) + WIN_WIDTH - 1) % WIN_WIDTH;
	int y2 = (int(y) + WIN_HEIGHT - 1) % WIN_HEIGHT;
	double value = 0.0;
	value += fractX * fractY * noise[y1 * WIN_WIDTH + x1];
	value += (1 - fractX) * fractY * noise[y1 * WIN_WIDTH + x2];
	value +=  fractX * (1 - fractY) * noise[y2 * WIN_WIDTH + x1];
	value += (1 - fractX) * (1 - fractY) * noise[y2 * WIN_WIDTH + x2];

	return (value);
}

double turbulence(double x, double y, double size, double *noise)
{
	double value;
	double init_size;

	value = 0.0;
	init_size = size;
	while (size >= 1)
	{
		value += smooth_noise(x / size, y / size, noise) * size;
		size /= 2.0;
	}
	return(128.0 * value / init_size);
}

void	draw_sky(t_mlx *mlx, int height, int width, double *noise)
{
	Uint8 
	mlx->img.data[count_h * WIN_WIDTH + count_w] = 0x993300 * smooth_noise(height, width, noise);//mlx->map_s->roof_color;
}

void	init_background(t_mlx *mlx)
{
	int		count_w;
	int		count_h;
	double *noise[WIN_HEIGHT * WIN_WIDTH]; 
	
	generate_noise(noise);
	count_h = -1;
	while (++count_h < WIN_HEIGHT)
	{
		count_w = -1;
		while (++count_w < WIN_WIDTH)
		{
			if (count_h > WIN_HEIGHT / 2)
				//draw_sky
				mlx->img.data[count_h * WIN_WIDTH + count_w] = 0x993300;//mlx->map_s->roof_color;
			else
				mlx->img.data[count_h * WIN_WIDTH + count_w] = 0x33CCFF;//mlx->map_s->floor_color;

		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
