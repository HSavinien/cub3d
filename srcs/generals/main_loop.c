/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/05 21:56:41 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, t_img *img)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	dprintf(2, "img at %p, ptr at %p, data at %p\n", img, img->img_ptr, img->data);//DEBUG
	int		x;
	int		y;

	x = 0;
	dprintf(2, "img of size %d * %d\n", img->width, img->height);//DEBUG
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
//			dprintf(2, "loop loop : x=%d, y=%d\n", x, y);//DEBUG
			if (y > img->height / 2)
				img_set_pixel(img, x, y, 0x00FF0000);
			else
				img_set_pixel(img, x, y, 0x0000FF00);
			y ++;
		}
		x ++;
	}
	dprintf(2, "exiting with x=%d, y=%d\n", x, y);//DEBUG
	(void) mlx;
	dprintf(2, "exiting %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
}

/* the function called by mlx_loop_hook.
 * it will call everything that must be done in this loop
 */
int	main_loop(t_mlx *mlx)
{
	dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	t_img	*main_disp_img;

	//create main display image
	main_disp_img = create_image(WIN_W, WIN_H, mlx);
	dprintf(2, "image created\n");//DEBUG
	if (!main_disp_img)
		return (0);
	//init this image with ground and ceiling color
	draw_background(mlx, main_disp_img);
	dprintf(2, "background drawn\n");//DEBUG
	//call raycasting function
	//display image
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, main_disp_img->img_ptr,
		0, 0);
	dprintf(2, "image on window\n");//DEBUG
	mlx_destroy_image(mlx->mlx_ptr, main_disp_img->img_ptr);
	free(main_disp_img);
	//add minimap
	return (0);
}
