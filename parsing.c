/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:05:22 by tmongell          #+#    #+#             */
/*   Updated: 2022/10/24 19:07:54 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ERR_OPEN_MSG " could not be oppened. check the file name and rights"
#define ERR_LINE_MSG "the line don't match any known patern"

void	check_file_name(char *name)
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

void	read_cub_file(int fd, t_map map_struct)
{
	char	*line;
	int		i;
	int		line_num;

	do while (line)
	{
		line = get_next_filled_line(fd, &line_num);
		while (ft_isspace(line[i++]))
			(void) i;
		if (ft_isupcase(line[i]))
			read_format_line(line, map_struct);
		else if (ft_isdigit(line[i]))
			read_map(line, fd, map_struct);
		else if line[i] == '#'
			continue;
		else
			error_mapfile(line_num, line, ERR_LINE_MSG, ERR_FILE_PATERN);
	}
}

t_map	*parsing(char	*map_file)
{
	int	map_fd;
	t_map	*map_struct;
	
	//check_name
	check_map_name(map_file);
	//try to open
	map_fd = open(map_file, O_RDONLY);
	if (map_fd < 0)
		ft_error(ft_strjoin(map_file, ERR_OPEN_MSG), ERR_OPEN);
	map_struct = malloc(sizeof(t_map));
	if (!map_struct)
		ft_error("unexpected malloc error in parsing", ERR_MALLOC);
	read_cub_file(fd, map_struct);
	return (map);
}
