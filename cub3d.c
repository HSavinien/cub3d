/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:32:26 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/17 08:15:30 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

//angles are in radiant. respectively 90, -90, 0, and 180 degrees.
#define NORTH_ANGLE (M_PI_2)
#define SOUTH_ANGLE (-M_PI_2)
#define EAST_ANGLE 0
#define WEST_ANGLE (M_PI)
/*
#define NORTH_ANGLE (1)
#define SOUTH_ANGLE (2)
#define EAST_ANGLE 3
#define WEST_ANGLE (4)
*/

void	set_player_position(t_map *map, t_mlx *mlx_s)
{
	mlx_s->player.pos_x = map->start_column + 0.5;
	mlx_s->player.pos_y = map->start_line + 0.5;
	if (map->start_dir == 'N')
		mlx_s->player.direction = NORTH_ANGLE;
	else if (map->start_dir == 'S')
		mlx_s->player.direction = SOUTH_ANGLE;
	else if (map->start_dir == 'E')
		mlx_s->player.direction = EAST_ANGLE;
	else if (map->start_dir == 'W')
		mlx_s->player.direction = WEST_ANGLE;
	else
		ft_error("entered redondant protection on player direction", ERR_WTF);
}

t_mlx	do_init(t_map *map)
{
	t_mlx		mlx_s;
	t_wall_img	*img;

	//init mlx
	mlx_s.mlx_ptr = mlx_init();
	mlx_s.map_s = map;
	//create img struct
	img = ft_calloc(1, sizeof(t_wall_img));
	//open textures
	img->north_img = read_img_file(map->north_path, mlx_s.mlx_ptr,
			&img->north_width, &img->north_height);
	img->south_img = read_img_file(map->south_path, mlx_s.mlx_ptr,
			&img->south_width, &img->south_height);
	img->east_img = read_img_file(map->east_path, mlx_s.mlx_ptr,
			&img->east_width, &img->east_height);
	img->west_img = read_img_file(map->west_path, mlx_s.mlx_ptr,
			&img->west_width, &img->west_height);
	mlx_s.wall = img;
	//init player
	set_player_position(map, &mlx_s);
	return (mlx_s);
}

void	init_move(t_mlx *mlx)
{
		mlx->key.forwd = 0;
		mlx->key.backwd = 0;
		mlx->key.left = 0;
		mlx->key.right = 0;
		mlx->key.rot_left = 0;
		mlx->key.rot_right = 0;
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	mlx_s;

	if (ac != 2)
		return (printf("error args\nusage : <%s> <file.cub>\n", av[0]));
	map = parsing(av[1]);
	mlx_s = do_init(&map);
	init_move(&mlx_s);
	//open window
	mlx_s.win_ptr = mlx_new_window(mlx_s.mlx_ptr, WIN_W, WIN_H, WIN_TITLE);
	//event hook
	mlx_hook(mlx_s.win_ptr, EVENT_WIN_CLOSE, 0, close_win, &mlx_s);
	mlx_hook(mlx_s.win_ptr, EVENT_KEY_PRESS, 0, keypress, &mlx_s);
	mlx_loop_hook(mlx_s.mlx_ptr, main_loop, (void *)(&mlx_s));
	mlx_hook(mlx_s.win_ptr, EVENT_KEY_RELEASE, 0, key_release, &mlx_s);
	//mlx loop
	mlx_loop(mlx_s.mlx_ptr);
}
