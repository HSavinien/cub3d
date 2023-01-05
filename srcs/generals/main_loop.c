/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/05 22:58:52 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, t_img *img)
{
	int		x;
	int		y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			if (y > img->height / 2)
				img_set_pixel(img, x, y, mlx->map_s->floor_color);
			else
				img_set_pixel(img, x, y, mlx->map_s->roof_color);
			y ++;
		}
		x ++;
	}
	(void) mlx;
}

void	draw_crosshair(t_mlx *mlx)
{
	t_img	cross;
	cross = mlx->sprites->crosshair;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, cross.img_ptr,
			WIN_W/2 - cross.width/2, WIN_H/2 - cross.height/2);
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
	//call raycasting function
	raycasting_start(mlx, main_disp_img);
	//display image
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
