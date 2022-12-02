/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:57:27 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/02 01:52:34 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MSG_IMG_FORMAT " is not a xpm or png file. please correct that"
#define MSG_XPM_OPEN " could not be oppened as a XPM, check name/right/content"

void	*read_img_file(char *file, void *mlx, int *img_w, int *img_h)
{
	void	*img;

	img = NULL;
	if (!ft_strcmp(ft_strrchr(file, '.'), ".xpm"))
		img = mlx_xpm_file_to_image(mlx, file, img_w, img_h);
//	else if (!ft_strcmp(ft_strrchr(file, '.'), ".png"))
//		img = mlx_png_file_to_image(mlx, file, img_w, img_h);
	else
		ft_error(ft_strjoin(file, MSG_IMG_FORMAT), ERR_IMG_OPEN);

	return (img);//debug
	if (!img)
		ft_error(ft_strjoin(file, MSG_XPM_OPEN), ERR_IMG_OPEN);
	return (img);
}

/* function that get a pointer, as a char*, to the pixel (x,y) in the image img.
 * the returned value is the first char of the pixel, aka the alpha chanel
 * a NULL pointer is returned if the pixel would be out of the image.
 * the last tree lines (get to the line y, get to column x of line, return)
 * could have been compresed in one. it wasn't for readability purpose.
 */
char	*img_get_pixel(t_img *img, int x, int y)
{
	char	*pixel;
	if (x > img->width || y > img->height)
		return (NULL);
	pixel = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l,
		&img->endian);
	pixel += y * img->width * 4;
	pixel += x * 4;
	return (pixel);
}

/* function that give the specified to the specified pixel in img.
 * color is an unsigned int with the structure A|R|G|B,
 * with B being the least significant byte.
*/
int	img_set_pixel(t_img *img, int x, int y, unsigned int color)
{
	unsigned int *pixel;
	
	pixel = (unsigned int*) img_get_pixel(img, x, y);
	if (!pixel)
		return (0);
	*pixel = color;
	return (1);
}
