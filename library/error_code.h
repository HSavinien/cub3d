/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:31:38 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/18 16:32:39 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* explicit error code are usefull in case of program error.
 * this file define the macro for each possible error.
 * it allow easier modification of error code when needed,
 * and can be checked to have more precision if the error message aren't clear
 */

#ifndef ERROR_CODE_H
# define ERROR_CODE_H

/*return values--------------------------------------------------return values*/

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
# define ERR_OPEN_MAP 10	//the map array is not closed
# define ERR_DUPLICATE 11	//the file contain twice the same data (eg two maps)
# define ERR_MAP_LAST 12	//map is not the last element of the file.

//system
# define ERR_MALLOC 13	//a malloc call failed to allocate memory
# define ERR_OPEN 14	//could not open a file, probably the map

//mlx
# define ERR_IMG_OPEN 15	//a sprite file cannot be opened.

//other
# define ERR_WTF -1		//entered a protection that should have been redundant

/*messages------------------------------------------------------------messages*/

# define MSG_MALLOC "a malloc call failed to allocate memory."

//parsing.c
#define MSG_FILE_OPEN " could not be oppened. Check the file name and rights."
#define MSG_LINE "the line don't match any known patern."
#define MSG_OMAP "the map is open. Please close the map."
#define MSG_MLTPLR "multiple player spawn detected."
#define MSG_MAP_CHAR "ilegal character found in map token."
#define MSG_FILE_DIR "map should be a file, not a directory. change your file."
//parsing_readfile.c
#define ERR_NB_TOKEN_MSG "wrong token number : exactly two token required"
#define ERR_WRONG_ID_MSG "unknown ID token. Valid ID are : [NO|SO|WE|EA|F|C]"
#define ERR_PATERN_MSG "that just don't make any sens!"
#define MSG_DUPLI "two map found in file. each file sould contain only one map"
#define MSG_MAP_LAST "no data can follow the map. Blame the subject, not me"
//parsing_read_color.c
#define MSG_COLORCODE "unrecognized color code. try hexa or RGB instead"
#define MSG_RGB_COMMA "misplaced comma in rgb code"
#define HEX_BASE "0123456789ABCDEF"
//parsing_missing_data.c
#define MSG_MAP "your map file is missing usefull data, namely THE F**KING MAP!"
#define MSG_DUP "data redefinition. the same entry can't appear twice"

#endif
