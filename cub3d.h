/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/01 17:06:43 by cmaroude         ###   ########.fr       */
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
	double	dir_x;//conflict with initialisation
	double	dir_y;//conflict with initialisation
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
	t_wall_img	*images;
	t_img		minimap;
	t_map		*map_s;
	t_img		img;
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
char	**get_tokenised_line(char *line);


//general utils
void	*destroy_array(char **array); //currently in error.c

//mlx utils
void	*read_img_file(char *file, void *mlx, int *img_w, int *img_h);


//error
void	*ft_error(char *msg, int ret);
void	err_mapfile(int line, char *content, char *msg, int code);
void	err_map_form(int pos[2], char **map, char *msg, int code);

//debug
void	show_struct(t_map *map_s);
void	show_map(char **map);//use a for loop, bad for the norm==================NORM

#endif
