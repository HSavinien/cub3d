/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 04:22:52 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/11 23:27:12 by tmongell         ###   ########.fr       */
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

# define WIN_W 1900	//window width. if program is too laggy, try lowering it
# define WIN_H 950	//window height.
//the angle of the field of view, in degree. try negative values for maximum lol
# define DEG_FOV 60
# define WALL_H	1	//the height of the wall. the bigger the higher
# define DEPTH	1	//how fast the wall will shrink when they are far

/*movement------------------------------------------------------------movement*/

# define MOVE_FORWARD KEY_W
# define MOVE_LEFT KEY_A
# define MOVE_BACKWARD KEY_S
# define MOVE_RIGHT KEY_D

# define TURN_LEFT KEY_ARROW_LEFT
# define TURN_RIGHT KEY_ARROW_RIGHT
# define SPEED 0.1
# define ROT_SPEED 1

#endif
