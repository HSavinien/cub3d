/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:57:27 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/23 23:55:21 by tmongell         ###   ########.fr       */
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
