/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/17 21:26:38 by tmongell         ###   ########.fr       */
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
#include "library/mlx_macos/mlx.h"
#include <key_code.h>
#include <mlx_event.h>

//project sublibrary
#include <error_code.h>
#include <libft/libft.h>
#include "config.h"

/*macros----------------------------------------------------------------macros*/

#define MAP_CHAR_OK "10NSEW \n" //char allowed to define the map

//value for map :
#define	WALL 1
#define FLOOR 2
#define H_DOOR 4
#define V_DOOR 8
#define OUTSIDE 255

//window values
#define WIN_TITLE "placeholder title"
#define FOV (DEG_FOV*M_PI/180)	//for more user-friendliness

/*structure---------------------------------------------------------structures*/

typedef unsigned char t_uchar;
typedef unsigned int t_uint;

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		width;
	int		height;
//those three must be here, don't ask what it's for
	int		size_l;	//the number of char in a line (nb_pixel * 4)
	int		bpp;	//bits per pixel
	int		endian;	//order of value in each pixel (I think?)
}	t_img;

typedef struct s_map {
	//display info
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
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
	double	direction;

}	t_entity;

typedef	struct	s_wall_img {
	void	*north_img;
	int		north_width;
	int		north_height;
	void	*south_img;
	int		south_width;
	int		south_height;
	void	*east_img;
	int		east_width;
	int		east_height;
	void	*west_img;
	int		west_width;
	int		west_height;
}	t_wall_img;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*win_ptr;
	t_wall_img	*wall;
	t_img		minimap;
	t_map		*map_s;
	t_img		main_img;
	t_entity	player;
}	t_mlx;

typedef	struct s_coord {
	double	x;
	double	y;
}	t_coord;

//used by raycasting function, store both the wall distance and orientation.
typedef	struct s_wall_data {
	double	distance;
	int		side;
	double	height;
	t_coord	pos;
} t_wall_data;


#include "chloutils.h"	//debug //tmp

/*prototypes--------------------------------------------------------prototypes*/
//parsing
t_map	parsing(char	*map_file);
void	read_cub_file(int fd, t_map *map);
void	check_missing_data(t_map *map);
void	check_duplicate(char *id, char *line, int line_num, t_map *map_s);
t_uint	read_color(char *color_code, char *full_line, int line_nb);

//display
void	raycasting_start(t_mlx *mlx, t_img *screen);
int		main_loop(t_mlx *mlx);
void	draw_wall(int ray_num, t_wall_data wall, t_img *screen);
int		wall_info(t_wall_data *data, t_coord ray, int face, t_entity *player);
void	get_ray_angle(t_mlx *mlx, double *angles);
void    get_next_pos(t_coord *ray, double dir, double slope, double offset);

//parsing utils
char	*get_next_filed_line(int fd, int *line);
char	**get_tokenised_line(char *line);


//general utils
void	*destroy_array(char **array);
int		sign(double nb);

//mlx utils
t_img	*create_image(int width, int height, t_mlx *mlx);
void	*read_img_file(char *file, void *mlx, int *img_w, int *img_h);
char	*img_get_pixel(t_img *img, int x, int y);
int		img_set_pixel(t_img *img, int x, int y, unsigned int color);
void	draw_figures(t_mlx *mlx, int i, int j);
void	draw_minimap(t_mlx *mlx);
void	init_window_images(t_mlx *mlx);
void	init_background(t_mlx *mlx);
void	init_minimap(t_mlx *mlx);
int		loop(t_mlx *mlx);
int		close_win(t_mlx *mlx);
int		event_hook(int key, t_mlx *mlx);

//error
void	*ft_error(char *msg, int ret);
void	err_mapfile(int line, char *content, char *msg, int code);
void	err_map_form(int pos[2], char **map, char *msg, int code);
void	*ret_free(void *ptr);

//debug
void	show_struct(t_map *map_s);
void	show_map(char **map);//use a for loop, bad for the norm==================NORM
void	draw_figures(t_mlx *mlx, int i, int j);
void	init_window_images(t_mlx *mlx);
void	init_background(t_mlx *mlx);
int		loop(t_mlx *mlx);

#endif
