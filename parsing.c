/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/21 19:15:32 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ERR_OPEN_MSG " could not be oppened. check the file name and rights"

void	check_map_name(char *name)
{
	char    *cut_name;

    cut_name = ft_strrchr(name, '/') + 1;
	if (!cut_name)
		cut_name = name;
	if (ft_strcmp(cut_name + ft_strlen(cut_name) - 4, ".cub"))
		ft_error("map name must be in '.cub' format", ERR_EXTENTION);
	else if (ft_strlen(cut_name) <= 4)
		ft_error("map name look empty", ERR_SHORT_NAME);
}

t_map	parsing(char	*map_file)
{
	int	fd;
	
	//check_name
	check_map_name(map_file);
	//try to open
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_error(ft_strjoin(map_file, ERR_OPEN_MSG), ERR_OPEN)

}
