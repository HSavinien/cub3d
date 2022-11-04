/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:31:38 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/04 18:33:13 by tmongell         ###   ########.fr       */
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
# define ERR_EXTENTION 1	//map name is not in .cub
# define ERR_SHORT_NAME 2	//map name is just '.cub'
# define ERR_FILE_PATERN 3	//a line in the .cub file doesn't make sens.
# define ERR_FILE_NB_TOKEN 4	//a data line isn't in "ID space DATA" form.
# define ERR_FILE_WRONG_ID 5	//a line ID in file does not match any known ID
# define ERR_MULTIPLAYER 6	//a second player start was found in the map
# define ERR_MAP_CHAR 7		//a forbiden char has been found in the map
# define ERR_COLORCODE 8	//a color code is not a valid rgb or hexa code
# define ERR_MISSING_DATA 9	//not all mandatory data have been specified in file
# define ERR_OPEN_MAP 10		//the map array is not closed
# define ERR_DUPLICATE 11	//the file contain twice the same data (eg two maps)

//system
# define ERR_MALLOC 12	//a malloc call failed to allocate memory
# define ERR_OPEN 13		//could not open a file, probably the map

//mlx
# define ERR_SPRITE 14	//a sprite file cannot be opened.

#endif
