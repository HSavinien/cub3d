/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:32:26 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/18 21:01:43 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//all angle are in degree, but we shall converte them into radian.
#define NORTH_ANGLE 90
#define SOUTH_ANGLE -90
#define EAST_ANGLE 0
#define WEST_ANGLE 180

t_mlx	do_init(t_map *map)
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
	mlx_s.player.pos_x = map->start_column;
	mlx_s.player.pos_y = map->start_line;
	if (map->direction == 'N')
		mlx_s.player.direction = NORTH_ANGLE;
	if (map->direction == 'S')
		mlx_s.player.direction = SOUTH_ANGLE;
	if (map->direction == 'E')
		mlx_s.player.direction = EAST_ANGLE;
	if (map->direction == 'W')
		mlx_s.player.direction = WEST_ANGLE;
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx_s;

	if (ac != 2)
		return(printf("error args\nusage : <%s> <file.cub>\n", av[0]));
	map = parsing(av[1]);
	mlx_s = do_init(&map)
	//open window
	mlx_s.win_ptr = mlx_new_window(mlx_s.mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	//event hook
	
	//mlx loop
	mlx_loop_hook(mlx_s.mlx_ptr, calculate_display, mlx_s);
	mlx_loop(mlx_s.mlx_ptr);
}