/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:32:26 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/29 01:19:00 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//angles are in radiant. respectively 90, -90, 0, and 180 degrees.
#define NORTH_ANGLE (M_PI/2)
#define SOUTH_ANGLE (-M_PI/2)
#define EAST_ANGLE 0
#define WEST_ANGLE (M_PI)

t_mlx	do_init(t_map *map)
{
	t_mlx	mlx_s;
	t_imgs	*img;

	//init mlx
	mlx_s.mlx_ptr = mlx_init();
	//create img struct
	img = ft_calloc(1, sizeof(t_imgs));
	//open textures
	img->north_img = read_img_file(map->north_path, mlx_s.mlx_ptr,
		&img->north_width, &img->north_height);
	img->south_img = read_img_file(map->south_path, mlx_s.mlx_ptr,
		&img->south_width, &img->south_height);
	img->east_img = read_img_file(map->east_path, mlx_s.mlx_ptr,
		&img->east_width, &img->east_height);
	img->west_img = read_img_file(map->west_path, mlx_s.mlx_ptr,
		&img->west_width, &img->west_height);
	mlx_s.images = img;
	//init player
	mlx_s.player.pos_x = map->start_column + 0.5;
	mlx_s.player.pos_y = map->start_line + 0.5;
	if (map->start_dir == 'N')
		mlx_s.player.direction = NORTH_ANGLE;
	else if (map->start_dir == 'S')
		mlx_s.player.direction = SOUTH_ANGLE;
	else if (map->start_dir == 'E')
		mlx_s.player.direction = EAST_ANGLE;
	else if (map->start_dir == 'W')
		mlx_s.player.direction = WEST_ANGLE;
	return (mlx_s);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx_s;

	if (ac != 2)
		return(printf("error args\nusage : <%s> <file.cub>\n", av[0]));
	map = parsing(av[1]);
	mlx_s = do_init(&map);
	//open window
	mlx_s.win_ptr = mlx_new_window(mlx_s.mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	//event hook
	
	//mlx loop
	//mlx_loop_hook(mlx_s.mlx_ptr, calculate_display, mlx_s);
	mlx_loop(mlx_s.mlx_ptr);
}
