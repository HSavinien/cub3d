/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:02:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/29 21:13:34 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* function that set the upper half of img in ceiling color,
 * and the lower half in floor color.
 */
void	draw_background(t_mlx *mlx, void *img)
{
	char	*first_pixel;

	first_pixel = mlx_get_data_addr(img, )
}

/* the function called by mlx_loop_hook.
 * it will call everything that must be done in this loop
 */
int	main_loop(t_mlx *mlx)
{
	void	*main_disp_img;

	//create main display image
	main_disp_img = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	//init this image with ground and ceiling color
	draw_background(mlx, main_disp_img);
	//call raycasting function
	//display image
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, main_disp_img, 0, 0);
	free(main_disp_img);
	//add minimap
	


	return (0);
}
