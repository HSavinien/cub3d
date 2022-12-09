/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:14:26 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/22 16:10:18 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include "cub3d.h"


int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return(printf("error args\nusage : <%s> <file.cub>\n", av[0]));
	map = parsing(av[1]);
	printf("\033[4;32mSUCCESS:\033[0m\nsucessfully read map of %d * %d char.\n",
			map.nb_line, map.nb_column);
//	system("leaks cub3d");
	printf("\n\033[4mtexture and color :\033[0m\n");
	printf("\t- NO : %s\n\t- SO : %s\n\t- EA : %s\n\t- WE : %s\n"
			"\t- Floor color : %X\n\t- Ceiling color : %X\n",
			map.north_path, map.south_path, map.west_path, map.east_path,
			(unsigned) map.floor_color, (unsigned) map.roof_color);
	printf("\n\033[4mraw map :\033[0m\n");
	for (int i = 0; i < map.nb_line; i++)
		printf("%s\n", map.raw_map[i]);
	printf("\n\033[4mparsed map :\033[0m\n");
	for (int i = 0; i < map.nb_line; i++)
	{
		for(int j = 0; map. parsed_map && map.parsed_map[i][j]; j ++)
			printf("%d", map.parsed_map[i][j]);
		printf("\n");
	}
	printf("\n\033[4mplayer info :\033[0m\n");
	printf("player start in [%d;%d], direction %c\n",
			map.start_line, map.start_column, map.start_dir);

}
