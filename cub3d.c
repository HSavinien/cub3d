/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:32:26 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/30 17:24:42 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//all angle are in degree, but we shall converte them into radian.
#define NORTH_ANGLE 90
#define SOUTH_ANGLE -90
#define EAST_ANGLE 0
#define WEST_ANGLE 180

/*t_mlx	do_init(t_map *map)
{
	t_mlx	mlx_s;
	
	//init mlx
	mlx_s.mlx_ptr = mlx_init();
	//open textures
	map->north_img = read_xpm_file(map->north_path, mlx_s.mlx_ptr);
	map->south_img = read_xpm_file(map->south_path, mlx_s.mlx_ptr);
	map->east_img = read_xpm_file(map->east_path, mlx_s.mlx_ptr);
	map->west_img = read_xpm_file(map->west_path, mlx_s.mlx_ptr);
	//init player
	mlx_s.player.pos_x = map-> mlx->img.datastart_column;
	mlx_s.player.pos_y = map->start_line;
	if (map->direction == 'N')
		mlx_s.player.direction = NORTH_ANGLE;
	if (map->direction == 'S')
		mlx_s.player.direction = SOUTH_ANGLE;
	if (map->direction == 'E')
		mlx_s.player.direction = EAST_ANGLE;
	if (map->direction == 'W')
		mlx_s.player.direction = WEST_ANGLE;
}*/

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx;

	if (ac != 2)
		return(printf("error args\nusage : <%s> <file.cub>\n", av[0]));
	map = parsing(av[1]);
//	mlx_s = do_init(&map)
	//open window
	init_window_images(&mlx);
	init_background(&mlx);
	//event hook
	mlx_hook(mlx.win_ptr, KEY_PRESS, 0, event_hook, &mlx);
	mlx_hook(mlx.win_ptr, DESTROY, 0, close_win, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, loop, &mlx);

	//mlx loop
	mlx_loop(mlx.mlx_ptr);
}
