/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/04 18:04:03 by tmongell         ###   ########.fr       */
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

//minilibX
#include <mlx.h>
#include <key_code.h>
#include <mlx_event.h>

//project sublibrary
#include <error_code.h>
#include <libft/libft.h>

/*macros----------------------------------------------------------------macros*/

#define MAP_CHAR_OK "10NSEW \n" //char allowed to define the map

//value for map :
#define	WALL 1
#define FLOOR 2
#define SPAWN FLOOR
#define DOOR 4
#define OUTSIDE 255

/*structure---------------------------------------------------------structures*/

typedef unsigned char t_uchar;
typedef unsigned int t_uint;

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
	t_uint	floor_color;
	t_uint	roof_color;
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

/*prototypes--------------------------------------------------------prototypes*/
//parsing
t_map	*parsing(char	*map_file);
void	read_cub_file(int fd, t_map *map);
void	check_missing_data(t_map *map);
void	check_duplicate(char *id, char *line, int line_num, t_map *map_s);
t_uint	read_color(char *color_code, char *full_line, int line_nb);
//parsing utils
char	*get_next_filed_line(int fd, int *line);


//general utils
void	*destroy_array(char **array); //currently in error.c

//error
void	ft_error(char *msg, int ret);
void	err_mapfile(int line, char *content, char *msg, int code);
void	err_map_form(int line, int column, char **map, char *msg, int code);
#endif
