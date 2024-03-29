/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2024/02/20 21:07:21 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*includes------------------------------------------------------------includes*/

/*standart library*/
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <math.h>

/*minilibX*/
# include <mlx.h>
# include "library/mlx_linux/mlx.h"
# include <key_code.h>
# include <mlx_event.h>

/*project sublibrary*/
# include <error_code.h>
# include <libft/libft.h>
# include "config.h"

/*macros----------------------------------------------------------------macros*/

# define MAP_CHAR_OK "10NSEWD \n" //char allowed to define the map

/*value for map :*/
# define WALL 1
# define FLOOR 2
# define DOOR_CL 4
# define DOOR_OP 8
# define OUTSIDE 255

/*window values*/
# define WIN_TITLE "placeholder title"
//# define FOV (DEG_FOV*M_PI/180)	//this macro's better, but norminette...
# define FOV 1.04719755	//a 60 degree angle
/*wall data values*/
# define NORTH_FACE 1
# define SOUTH_FACE 2
# define EAST_FACE 3
# define WEST_FACE 4
# define DOOR_CL_FACE 5
# define DOOR_OP_FACE 6

/*constantes*/
# define EPSILON 0.00001

/*hand annimation values*/
# define MAX_FRAME	10

/*easter_egg : fractal ground/roof*/
# define MANDELBROT 1
# define JULIA 2
/*structure---------------------------------------------------------structures*/

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

typedef struct s_key_data
{
	int	forwd;
	int	backwd;
	int	left;
	int	right;
	int	rot_left;
	int	rot_right;
	int	shooting;
}	t_key_data;

typedef struct s_img
{
	void	*img_ptr;
	int		*data;
	int		width;
	int		height;
	int		size_l;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_map {
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	long	floor_color;
	long	roof_color;
	char	*crosshair;
	char	*door_closed;
	char	*door_opened;
	char	**raw_map;
	t_uchar	**parsed_map;
	int		nb_line;
	int		nb_column;
	int		start_line;
	int		start_column;
	char	start_dir;
}	t_map;

typedef struct s_entity {
	double	pos_x;
	double	pos_y;
	double	direction;

}	t_entity;

typedef struct s_utils_img {
	t_img	north_wall;
	t_img	south_wall;
	t_img	east_wall;
	t_img	west_wall;
	t_img	door_closed;
	t_img	door_opened;
	t_img	crosshair;
	t_img	compass;
}	t_utils_img;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*win_ptr;
	t_utils_img	*sprites;
	t_img		minimap;
	t_img		*main_disp_img;
	t_map		*map_s;
	t_entity	player;
	t_key_data	key;
}	t_mlx;

typedef struct s_coord {
	double	x;
	double	y;
}	t_coord;

typedef struct s_recast_data {
	double	angle;
	int		ray_num;
}	t_cast_data;

typedef struct s_point_map
{
	int	i;
	int	j;
}	t_pt_map;

/*used by raycasting function, store both the wall distance and orientation.*/
typedef struct s_wall_data {
	t_coord	pos;
	double	distance;
	double	height;
	int		side;
	t_img	*texture;
	int		texture_col;
}	t_wall_data;

typedef struct s_vector
{
	t_coord	pos;
	t_coord	dir;
	t_coord	len;
}	t_vec;

/*prototypes--------------------------------------------------------prototypes*/
/*----------------------------------parsing-----------------------------------*/
t_map	parsing(char	*map_file);
void	read_cub_file(int fd, t_map *map);
void	check_missing_data(t_map *map);
void	check_duplicate(char *id, char *line, int line_num, t_map *map_s);
t_uint	read_color(char *color_code, char *full_line, int line_nb);

/*----------------------------------display-----------------------------------*/
void	raycasting_start(t_mlx *mlx, t_img *screen);
void	draw_wall_img(int ray_num, t_wall_data wall, t_img *screen, t_mlx *mlx);
int		wall_info(t_wall_data *data, t_coord ray, int face, t_entity *player);
int		get_type(t_map *map, int x, int y, int wall_side);
void	get_ray_angle(t_mlx *mlx, double *angles);
void	get_next_pos(t_coord *ray, double dir, double slope, double offset);

/*-------------------------------parsing utils--------------------------------*/
char	*get_next_filed_line(int fd, int *line);
char	**get_tokenised_line(char *line);
int		is_line_empty(char *str);

/*----------------------------------general-----------------------------------*/
/* main_loop.c */
int		main_loop(t_mlx *mlx);

/* collision.c */
int		verif_pos(double x, double y, t_mlx *mlx, double buf);
int		verif_col(double x, double y, t_mlx *mlx);

/*-------------------------------general utils--------------------------------*/
void	*destroy_array(char **array);
int		sign(double nb);
double	simplify_angle_full(double angle);
double	simplify_angle_half(double angle);
double	get_line_angle(double side1, double side2);
double	get_point_dist(t_coord a, t_coord b);

/*---------------------------------mlx utils----------------------------------*/
t_img	*create_image(int width, int height, t_mlx *mlx);
t_img	read_img_file(char *file, void *mlx);
t_img	read_img_file_soft(char *file, void *mlx);
int		img_get_pixel(t_img *img, int x, int y);
int		img_set_pixel(t_img *img, int x, int y, unsigned int color);

/*-----------------------------------event------------------------------------*/
/* key_event.c */
int		close_win(t_mlx *mlx);
void	toogle_mouse(t_mlx *mlx_s);
int		keypress(int key, t_mlx *mlx);
int		mouse_press(int key, t_mlx *mlx);
int		key_release(int key, t_mlx *mlx);

/* hook.c */
int		mouse_move(int mouse_x, int mouse_y, t_mlx *mlx);
void	do_rotate(t_mlx *mlx, int mouse);
int		event_hook(t_mlx *mlx);

/* hook_utils.c */
t_vec	init_data_dir(t_mlx *mlx);
double	rad_to_degree(double rad);

/*-----------------------------------bonus------------------------------------*/
/*draw_bonus.c*/
void	init_minimap(t_mlx *mlx);
void	draw_bonus(t_mlx *mlx);
void	animate_hand(t_mlx *mlx);

/*draw_minimap.c*/
void	draw_figures(t_mlx *mlx, t_pt_map i, t_pt_map j);
void	draw_minimap(t_mlx *mlx);

/* toogle_bonus.c */
void	toogle_door(t_mlx *mlx_s);
void	toogle_mouse(t_mlx *mlx_s);

/*fractol*/
void	draw_fractal(t_mlx *mlx, t_img *img, int y, int type);

/*-----------------------------------error------------------------------------*/
void	*ft_error(char *msg, int ret);
void	err_mapfile(int line, char *content, char *msg, int code);
int		err_map_form(int pos[2], char **map, char *msg, int code);
void	*ret_free(void *ptr);

/*-----------------------------------debug------------------------------------*/
void	show_struct(t_map *map_s);
/*use a for loop, bad for the nor==============NORM*/
void	show_map(char **map);

#endif
