/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/07 22:50:05 by tmongell         ###   ########.fr       */
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
				img_set_pixel(img, x, y, 0xFF0000);
			else
				img_set_pixel(img, x, y, 0x00FF00);
			y ++;
		}
		x ++;
	}
	(void) mlx;
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
	//display image
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, main_disp_img->img_ptr,
		0, 0);
	mlx_destroy_image(mlx->mlx_ptr, main_disp_img->img_ptr);
	free(main_disp_img);
	//add minimap
	return (0);
}