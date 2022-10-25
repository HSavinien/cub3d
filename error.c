/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:05:19 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/25 20:16:45 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* general error function :
 * display an error message, 
 * then exit with the given code
 */
void	ft_error(char *msg, int ret)
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
	printf("Error %d : unrecognized data patern in .cub file, line %d\n"
		"%s\n", code, line, msg);
	printf("\033[4,91m%s\033[0m\n", content);
	exit(code);
}
/*
static void	print_map_line(char *line, int err_column)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (i == line && j == column)
				printf("\033[0;7;31m%c\033[0m", map[i][j]);
			else if (line[i][j] == '1')
				printf("\033[0;7m%c\033[0m", map[i][j]);
			else if (line[i][j] == '1')
				printf("\033[0;7m%c\033[0m", map[i][j]);
			else if (char_is_set(line[i][j], "NSWE"))
				printf("\033[0;44m%c\033[0m", map[i][j]);
			else 
				printf("\033[0m%c\033[0m", map[i][j]);
			j ++;
		}
		i ++;
	}
}
*/

/* used to give detailled error message when map is incorectly formated.
 * line is the line from the start of the line, not the start of the file;
 * column is the column where the problem take place
 */
void	err_map_form(int line, int column, char **map, char *msg, int code)
{
	int	i;
	int	j;

	printf("Error %d : %s\n",code, msg);
	printf("error is on line %d, column %d\n", line, column);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == line && j == column)
				printf("\033[0;7;31m%c\033[0m", map[i][j]);
			else if (map[i][j] == '1')
				printf("\033[0;7m%c\033[0m", map[i][j]);
			else if (map[i][j] == '1')
				printf("\033[0;7m%c\033[0m", map[i][j]);
			else if (map[i][j] == '0')
				printf("\033[0;7;90m%c\033[0m", map[i][j]);
			else if (char_in_set(map[i][j], "NSWE"))
				printf("\033[0;7;34m%c\033[0m", map[i][j]);
			else if (ft_isspace(map[i][j])) 
				printf("\033[0m%c\033[0m", map[i][j]);
			j ++;
		}
		printf("\n");
		i ++;
	}
	exit(code);
}
