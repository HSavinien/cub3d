/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/17 23:41:54 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
/*function that draw a fractal on half the background. arguments are :
 * 		mlx : the usual mlx struct;
 * 		img : the background image where to draw;
 * 		is_floor : if the half of the image is the top or botom one
 * 		type : the type of fractal to draw (MANDELBROT or JULIA)
 */
void	draw_fractal(t_mlx *mlx, t_img *img, char is_floor, int type)
{
	int	x;
	int	y;
	int	stop;

	if (is_floor)
	{
		y = WIN_H / 2;
		stop = WIN_H;
	}
	else
	{
		y = 0;
		stop = WIN_H / 2;
	}
	while (y < stop)
	{
		x = 0;
		while (x < WIN_W)
		{
			img_set_pixel(
					img, x , y, (x  + y) % 255
					| (x * y) << 16
					| (x & y) << (type + 8) );
			x ++;
		}
		y ++;
	}
	(void) mlx;
}

void	fill_background(t_mlx *mlx, t_img *img, char is_floor, int color)
{
	int	x;
	int	y;
	int	stop;

	if (is_floor)
	{
		y = WIN_H / 2;
		stop = WIN_H;
	}
	else
	{
		y = 0;
		stop = WIN_H / 2;
	}
	while (y < stop)
	{
		x = 0;
		while (x < WIN_W)
			img_set_pixel(img, x ++, y, color);
		y ++;
	}
	(void) mlx;
}

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, t_img *img)
{
	//draw ceiling
	if (mlx->map_s->roof_color > 0xFFFFFF)
		draw_fractal(mlx, img, 0, mlx->map_s->roof_color >> 24);
	else
		fill_background(mlx, img, 0, mlx->map_s->roof_color);
	//draw floor
	if (mlx->map_s->floor_color > 0xFFFFFF)
		draw_fractal(mlx, img, 1, mlx->map_s->floor_color >> 24);
	else
		fill_background(mlx, img, 1, mlx->map_s->floor_color);
}

void	draw_crosshair(t_mlx *mlx)
{
	t_img	cross;

	cross = mlx->sprites->crosshair;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, cross.img_ptr,
		WIN_W / 2 - cross.width / 2, WIN_H / 2 - cross.height / 2);
}

/* the function called by mlx_loop_hook.
 * it will call everything that must be done in this loop
 */
int	main_loop(t_mlx *mlx)
{
	t_img	*main_disp_img;

	//create main display image
	main_disp_img = create_image(WIN_W, WIN_H, mlx);
	if (!main_disp_img)
		return (0);
	//init this image with ground and ceiling color
	draw_background(mlx, main_disp_img);
	event_hook(mlx);
	//call raycasting function
	raycasting_start(mlx, main_disp_img);
	//display image
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, main_disp_img->img_ptr,
		0, 0);
	mlx_destroy_image(mlx->mlx_ptr, main_disp_img->img_ptr);
	free(main_disp_img);
	//add minimap
	init_minimap(mlx);
	draw_minimap(mlx);
	draw_crosshair(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->minimap.img_ptr);
	mlx->minimap.img_ptr = NULL;
	return (0);
}
