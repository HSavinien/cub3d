/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:05:19 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/18 22:18:37 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* general error function :
 * display an error message, 
 * then exit with the given code
 */
void	*ft_error(char *msg, int ret)
{
	printf("Error %d :\n%s\n", ret, msg);
	exit(ret);
}

/* error function made to acuratly display error in .cub files :
 * first, it give a general error message, giving the line and column,
 * as well as the error code of the error. then an optional precision message,
 * then display the problematic line and highlight the problematic part;
 */
void	err_mapfile(int line, char *content, char *msg, int code)
{
	printf("Error %d : unrecognized patern in file :\n\t%s\n\n", code, msg);
	printf("on line (%d) : \033[4;91m%s\033[0m\n", line, content);
	exit(code);
}

//function used by err_map_form to put the map on screen
static void	print_map_char(char c)
{
	if (c == '1')
		printf("\033[0;7m%c\033[0m", c);
	else if (c == '0')
		printf("\033[0;7;90m%c\033[0m", c);
	else if (char_in_set(c, "NSWE"))
		printf("\033[0;7;34m%c\033[0m", c);
	else if (ft_isspace(c))
		printf("\033[0m%c\033[0m", c);
	else if (c == 'D')
		printf("\033[0;97;100m%c\033[0m", c);
	else
		printf("\033[0;7;31m%c\033[0m", c);
}

/* used to give detailled error message when map is incorectly formated.
 * line is the line from the start of the line, not the start of the file;
 * column is the column where the problem take place
 */
void	err_map_form(int pos[2], char **map, char *msg, int code)
{
	int	i;
	int	j;

	printf("Error %d at [%d;%d]: %s\n\n", code, pos[0], pos[1], msg);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == pos[0] && j == pos[1])
				printf("\033[0;7;31m%c\033[0m", map[i][j]);
			else
				print_map_char(map[i][j]);
			j ++;
		}
		printf("\n");
		i ++;
	}
	exit(code);
}

/* work just like the normal free, but return a NULL pointer after freeing.
 * usefull to gain lines in protection.
 */
void	*ret_free(void	*ptr)
{
	free(ptr);
	return (NULL);
}
