/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/02 01:52:24 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, t_img *img)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	int		x;
	int		y;

	y = 0;
	while (y <= img->height / 2)
	{
		dprintf(2, "loop : drawing line %d\n", y);//DEBUG
		x = 0;
		while (x <= img->width)
			dprintf(2, "loop : drawing pixel %d\n", x);//DEBUG
			img_set_pixel(img, x++, y, mlx->map_s->roof_color);
		y ++;
	}
	dprintf(2, "ceiling drawn\n");//DEBUG
	while (y <= img->height)
	{
		x = 0;
		while (x <= img->width)
			img_set_pixel(img, x++, y, mlx->map_s->roof_color);
		y ++;
	}
	dprintf(2, "floor drawn\n");//DEBUG
}

/* the function called by mlx_loop_hook.
 * it will call everything that must be done in this loop
 */
int	main_loop(t_mlx *mlx)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	t_img	main_disp_img;

	//create main display image
	main_disp_img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	dprintf(2, "created image\n");//DEBUG
	//init this image with ground and ceiling color
	draw_background(mlx, &main_disp_img);
	dprintf(2, "generated background\n");//DEBUG
	//call raycasting function
	//display image
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, main_disp_img.img_ptr,
		0, 0);
	dprintf(2, "image put on window\n");//DEBUG
	mlx_destroy_image(mlx->mlx_ptr, main_disp_img.img_ptr);
	//add minimap
	


	exit(0);
	return (0);
}
