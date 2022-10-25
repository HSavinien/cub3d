/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:25:40 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/24 17:32:12 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* explicit error code are usefull in case of program error.
 * this file define the macro for each possible error.
 * it allow easier modification of error code when needed,
 * and can be checked to have more precision if the error message aren't clear
 */

#ifndef ERROR_CODE_H
# define ERROR_CODE_H

//parsing
# define ERR_EXTENTION	//map name is not in .ber
# define ERR_SHORT_NAME //map name is less than 4 char, so it's just '.cub'
# define ERR_FILE_PATERN	//a line in the .cub file doesn't make sens.

//system
# define ERR_MALLOC	//a malloc call failed to allocate memory
# define ERR_OPEN	//could not open a file, probably the map

//mlx
# define ERR_SPRITE	//a sprite file cannot be opened.

#endif
