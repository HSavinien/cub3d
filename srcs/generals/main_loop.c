/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2023/07/09 02:30:46 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define REF_ANGLE 0.4

char	point_on_radius(int x, int y) {
    int center_x = WIN_W / 2;
    int center_y = WIN_H / 2;

    float angle = atan2(y - center_y, x - center_x);
    if (angle < 0) {
        angle += 2 * M_PI;
    }

    if (fabs(angle - M_PI / 2) <= 0.02 || fabs(fmod(angle - fabs(M_PI/2 + REF_ANGLE), REF_ANGLE)) <= 0.02) {
        return 1;
	}

    return 0;
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
		while (x < WIN_W) {
			if (GRID_STRENGHT && is_floor && (y % 32 < 3 || point_on_radius(x,y)))
				img->data[y * img->width + x ++] = (color - GRID_STRENGHT) | BACKGROUND_TR<< 24;
			else
				img->data[y * img->width + x ++] = color | BACKGROUND_TR << 24;
		}
		y ++;
	}
	(void) mlx;
}

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, t_img *img)
{
	if (mlx->map_s->roof_color > 0xFFFFFF)
		draw_fractal(mlx, img, 0, mlx->map_s->roof_color >> 24);
	else
		fill_background(mlx, img, 0, mlx->map_s->roof_color);
	if (mlx->map_s->floor_color > 0xFFFFFF)
		draw_fractal(mlx, img, WIN_H / 2, mlx->map_s->floor_color >> 24);
	else
		fill_background(mlx, img, 1, mlx->map_s->floor_color);
}

/* the function called by mlx_loop_hook.
 * it will call everything that must be done in this loop
 */
int	main_loop(t_mlx *mlx)
{
	draw_background(mlx, mlx->main_disp_img);
	event_hook(mlx);
	raycasting_start(mlx, mlx->main_disp_img);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->main_disp_img->img_ptr, 0, 0);
	draw_bonus(mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->minimap.img_ptr);
	mlx->minimap.img_ptr = NULL;
	return (0);
}
