/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:14:55 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/21 17:08:59 by tmongell         ###   ########.fr       */
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

//project sublibrary
#include <key_code.h>
#include <mlx_event.h>

/*macros----------------------------------------------------------------macros*/

/*structure---------------------------------------------------------structures*/

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
	int		floor_color;
	int		roof_color;
	//the map itself
	char	**raw_map;
	int		**parsed_map;	//put it there, but I'm not sure it's usefull
	//player info
	int		start_x;
	int		start_y;
	int		start_dir;
	
}	t_map;

/*prototypes--------------------------------------------------------prototypes*/

#endif
