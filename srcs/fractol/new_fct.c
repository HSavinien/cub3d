/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:48:34 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/21 12:31:14 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <cub3d.h>

t_fractol_data	init_fractol_data(t_mlx *mlx, int fractal)
{
	t_fractol_data	data;

	//init function
	if (fractal == MANDELBROT)
		data.function = &mandelbrot_point;
	else
		data.function = julia_point;
	//init phase
	data.phase = (int)mlx->player.direction % 10;
	//init offx
	data.offx = -mlx->player.pos_x;
	//init offy
	data.offy = -mlx->player.pos_y / 2;
	return (data);
}

/*function that draw a fractal on half the background. arguments are :
 * 		mlx : the usual mlx struct;
 * 		img : the background image where to draw;
 * 		is_floor : if the half of the image is the top or botom one
 * 		type : the type of fractal to draw (MANDELBROT or JULIA)
 */
void	draw_fractal(t_mlx *mlx, t_img *img, int y, int type)
{
	int				stop_line;
	int				x;
	t_fractol_data	data;
	t_ncomp 		c;

	//dertermine if we go from 0 to WIN_H/2 or to WIN_H/2 to WIN_H
	stop_line = y + WIN_H/2;
	//init necessary data for fractol
	data = init_fractol_data(mlx, type);
	y = 0;
	while (y < stop_line)
	{
		x = 0;
		while (x < WIN_W)
		{
			c.re = x * (4 / WIN_W) + data.offx;
			c.im = y * (2 / WIN_H) + data.offy;
			img_set_pixel(img, x, y, couleur_pixel(
				data.phase, data.function(c, data.c)));
			x ++;
		}
		y ++;
	}
}
