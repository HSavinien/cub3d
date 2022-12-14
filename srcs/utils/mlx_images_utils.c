/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:57:27 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/05 13:46:48 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MSG_IMG_OPEN " could not be oppened as a XPM, check name/right/content"

t_img	read_img_file(char *file, void *mlx)
{
	t_img	img;

	img.img_ptr = NULL;
		img.img_ptr = mlx_xpm_file_to_image(mlx, file, &img.width, &img.height);
	if (!img.img_ptr)
		ft_error(ft_strjoin(file, MSG_IMG_OPEN), ERR_IMG_OPEN);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l,
			&img.endian);
	return (img);
}

/*allocate an image struct, then create an image of specified size.
 * it also init the differents values inside the image struct.
 * if it fail, it don't exit the program but return NULL
 * */
t_img	*create_image(int width, int height, t_mlx *mlx)
{
	t_img	*new;

	new = ft_calloc (1, sizeof(t_img));
	if (!new)
		return (NULL);
	new->img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
	if (!new->img_ptr)
		return (ret_free(new));
	new->data = (int *)mlx_get_data_addr(new->img_ptr, &new->bpp, &new->size_l,
			&new->endian);
	new->width = width;
	new->height = height;
	return (new);
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

	if (x > img->width || y > img->height || img->data)
		return (NULL);
	pixel = (char *)img->data;
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
	img->data[y * img->width + x] = color;
	return (1);
}
