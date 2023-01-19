/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:32:26 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/19 13:41:21 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

//angles are in radiant. respectively 90, -90, 0, and 180 degrees.
#define NORTH_ANGLE (-M_PI_2)
#define SOUTH_ANGLE (M_PI_2)
#define EAST_ANGLE (M_PI)
#define WEST_ANGLE 0

#define DEFAULT_CROSSHAIR "./sprites/default_crosshair.xpm"
#define DEFAULT_DOOR_CL "./sprites/default_door_closed.xpm"
#define DEFAULT_DOOR_OP "./sprites/default_door_opened.xpm"

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

void	do_init_bonus(t_mlx *mlx_s, t_map *map)
{
	if (map->crosshair)
		mlx_s->sprites->crosshair =
			read_img_file(map->crosshair, mlx_s->mlx_ptr);
	else
		mlx_s->sprites->crosshair =
			read_img_file(DEFAULT_CROSSHAIR, mlx_s->mlx_ptr);
	if (map->door_closed)
		mlx_s->sprites->door_closed =
			read_img_file(map->door_closed, mlx_s->mlx_ptr);
	else
		mlx_s->sprites->door_closed =
			read_img_file(DEFAULT_DOOR_CL, mlx_s->mlx_ptr);
	if (map->door_opened)
		mlx_s->sprites->door_opened =
			read_img_file(map->door_opened, mlx_s->mlx_ptr);
	else
		mlx_s->sprites->door_opened =
			read_img_file(DEFAULT_DOOR_OP, mlx_s->mlx_ptr);

}

t_mlx	do_init(t_map *map)
{
	t_mlx		mlx_s;

	//init mlx
	mlx_s.mlx_ptr = mlx_init();
	mlx_s.map_s = map;
	//create img struct
	mlx_s.sprites = ft_calloc(1, sizeof(t_utils_img));
	if (!mlx_s.sprites)
		ft_error(MSG_MALLOC, ERR_MALLOC);
	//open wall textures
	mlx_s.sprites->north_wall = read_img_file(map->north_path, mlx_s.mlx_ptr);
	mlx_s.sprites->south_wall = read_img_file(map->south_path, mlx_s.mlx_ptr);
	mlx_s.sprites->east_wall = read_img_file(map->east_path, mlx_s.mlx_ptr);
	mlx_s.sprites->west_wall = read_img_file(map->west_path, mlx_s.mlx_ptr);
	//open other sprites
	do_init_bonus(&mlx_s, map);
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
		mlx->key.pos_x = 0;
		mlx->key.turn = 0;
		mlx->key.dist = 0;
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
	//mlx_hook(mlx_s.win_ptr, EVENT_BUTTON_PRESS, 0, mouse_press, &mlx_s);
	mlx_hook(mlx_s.win_ptr, EVENT_MOTION, 0, mouse_move, &mlx_s);
	mlx_loop_hook(mlx_s.mlx_ptr, main_loop, (void *)(&mlx_s));
	mlx_hook(mlx_s.win_ptr, EVENT_KEY_RELEASE, 0, key_release, &mlx_s);
	//mlx loop
	mlx_loop(mlx_s.mlx_ptr);
}
