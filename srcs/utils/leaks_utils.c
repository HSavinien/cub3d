/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:srcs/utils/leaks_utils.c
/*   Created: 2022/11/21 20:57:03 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/22 17:01:47 by tmongell         ###   ########.fr       */
=======
/*   Created: 2022/11/22 16:48:16 by cmaroude          #+#    #+#             */
/*   Updated: 2022/11/23 09:37:24 by cmaroude         ###   ########.fr       */
>>>>>>> 1a034aacbf3e9156e0c9f15fe51eaa96b2a40a35:hook.c
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*destroy_array(char **array)
{
<<<<<<< HEAD:srcs/utils/leaks_utils.c
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
=======
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit (0);
}

int		event_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		close_win(mlx);
	return (0);
>>>>>>> 1a034aacbf3e9156e0c9f15fe51eaa96b2a40a35:hook.c
}
