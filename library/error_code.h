/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:25:40 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/27 17:27:58 by tmongell         ###   ########.fr       */
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
# define ERR_EXTENTION	//map name is not in .cub
# define ERR_SHORT_NAME //map name is less than 4 char, so it's just '.cub'
# define ERR_FILE_PATERN	//a line in the .cub file doesn't make sens.
# define ERR_FILE_NB_TOKEN	//a line in the file isn't in "ID space DATA" form.
# define ERR_FILE_WRONG_ID	//a line ID in file does not match any known ID

//system
# define ERR_MALLOC	//a malloc call failed to allocate memory
# define ERR_OPEN	//could not open a file, probably the map

//mlx
# define ERR_SPRITE	//a sprite file cannot be opened.

#endif
