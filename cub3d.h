/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/23 12:12:53 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*includes------------------------------------------------------------includes*/

//standart library
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <math.h>

//minilibX
#include <mlx.h>
#include <key_code.h>
#include <mlx_event.h>

//project sublibrary
#include <error_code.h>
#include <libft/libft.h>

/*macros----------------------------------------------------------------macros*/

#define MAP_CHAR_OK "10NSEW \n" //char allowed to define the map
#define TO_COORD(X,Y) ((int)floor(Y) * IMG_WIDTH + (int)floor(X))
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define MOUSE_DOWN 4
#define MOUSE_UP 5
#define MOUSE_MOVE 6
#define EXPOSE 12
#define DESTROY 17

//value for map :
#define	WALL 1
#define FLOOR 2
#define H_DOOR 4
#define V_DOOR 8
#define OUTSIDE 255

//window values
#define WIN_W 1080
#define WIN_H 720
#define WIN_TITLE "placeholder title"
#define TSIZE 32
#define	TILE_SMM 8
#define WIN_WIDTH 15 * TSIZE
#define WIN_HEIGHT 11 * TSIZE
#define IMG_WIDTH 15 * TILE_SMM
#define IMG_HEIGHT 11 * TILE_SMM

/*structure---------------------------------------------------------structures*/

typedef unsigned char t_uchar;
typedef unsigned int t_uint;

typedef struct s_xpm
{
	void	*wall;
	int		width;
	int		height;
}	t_xpm;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_map {
	//display info
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	void	*north_img;
	void	*south_img;
	void	*east_img;
	void	*west_img;
	long	floor_color;
	long	roof_color;
	//the map itself
	char	**raw_map;
	t_uchar	**parsed_map;
	int		nb_line;
	int		nb_column;		//the len of the longest line.
	//player info
	int		start_line;
	int		start_column;
	char	start_dir;
}	t_map;

//struct meant to characterise any player or NPC in the game
typedef	struct	s_entity {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_entity;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		minimap;
	t_map		*map_s;
	t_img		img;
	t_xpm		xpm;
	t_entity	player;
}	t_mlx;

/*prototypes--------------------------------------------------------prototypes*/
//parsing
t_map	parsing(char	*map_file);
void	read_cub_file(int fd, t_map *map);
void	check_missing_data(t_map *map);
void	check_duplicate(char *id, char *line, int line_num, t_map *map_s);
t_uint	read_color(char *color_code, char *full_line, int line_nb);

//parsing utils
char	*get_next_filed_line(int fd, int *line);


//general utils
void	*destroy_array(char **array); //currently in error.c
void	draw_figures(t_mlx *mlx, int i, int j);
void	draw_minimap(t_mlx *mlx);
void	init_window_images(t_mlx *mlx);
void	init_background(t_mlx *mlx);
void	init_minimap(t_mlx *mlx);
int		loop(t_mlx *mlx);
int		close_win(t_mlx *mlx);
int		event_hook(int key, t_mlx *mlx);

//error
void	ft_error(char *msg, int ret);
void	err_mapfile(int line, char *content, char *msg, int code);
void	err_map_form(int pos[2], char **map, char *msg, int code);

//debug
void	show_struct(t_map *map_s);
void	show_map(char **map);//use for, bad for the norm========================NORM

#endif
