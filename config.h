/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 04:22:52 by tmongell          #+#    #+#             */
/*   Updated: 2023/07/15 01:34:55 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# include "cub3d.h"

/*
 * used to store default values that the user might want to customize,
 * like window size, FOV...
 * a more modern game would have used a .ini file, but macro are easier to use.
 * plus, I don't wana do more parsing...
 */

/*display--------------------------------------------------------------display*/
//window width. can impact performance if to big
# define WIN_W 800	//default 800, fullscreen 1920
//window height. can impact performance if to big
# define WIN_H 600	//default 600, fullscreen 1035.

//the angle of the field of view, in degree. non fonctionnal for norm reason
# define DEG_FOV 60	//default 60

//the height of the wall. the bigger the higher
# define WALL_H	1	//default 1

//how fast the wall will shrink when they are far (work weird)
#define DEPTH	1	//default 1

//synthwave addon
//background transparence, for motion blur effect
# define BACKGROUND_TR 192 // default : ON 192; OFF 0

//relation between normal floor color and the color of the grid.
# define GRID_STRENGHT 0//0x0f0f0f //default : ON 0x0f0f0f; OFF 0x0

/*movement------------------------------------------------------------movement*/

# define MOVE_FORWARD KEY_W		//default KEY_W
# define MOVE_LEFT KEY_A		//default KEY_A
# define MOVE_BACKWARD KEY_S	//default KEY_S
# define MOVE_RIGHT KEY_D		//default KEY_D

# define TURN_LEFT KEY_ARROW_LEFT	//default KEY_ARROW_LEFT
# define TURN_RIGHT KEY_ARROW_RIGHT	//default KEY_ARROW_RIGHT

# define SPEED 0.1		//default 0.1
# define ROT_SPEED 1	//default 1

# define ACT_KEY KEY_SPACE		//default KEY_SPACE
# define MOUSE_TGLE KEY_TILD	//default KEY_TILD

#endif
