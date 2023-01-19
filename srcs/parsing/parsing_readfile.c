/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:32 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/18 19:25:39 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_format_line_optional(char **tokenised_line, t_map *map_struct)
{
	if (!strcmp(tokenised_line[0], "CR"))
		map_struct->crosshair = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "DC"))
		map_struct->door_closed = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "DO"))
		map_struct->door_opened = ft_strdup(tokenised_line[1]);
	else
		return (0);
	return (1);
}

void	read_format_line(char *line, t_map *map_struct, int line_nb)
{
	char	**tokenised_line;

	tokenised_line = get_tokenised_line(line);
	if (!tokenised_line || !tokenised_line[0] || !tokenised_line[1]
		|| tokenised_line[2])
		err_mapfile(line_nb, line, ERR_NB_TOKEN_MSG, ERR_FILE_NB_TOKEN);
	check_duplicate(tokenised_line[0], line, line_nb, map_struct);
	if (!strcmp(tokenised_line[0], "NO"))
		map_struct->north_path = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "SO"))
		map_struct->south_path = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "WE"))
		map_struct->west_path = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "EA"))
		map_struct->east_path = ft_strdup(tokenised_line[1]);
	else if (!strcmp(tokenised_line[0], "F"))
		map_struct->floor_color = read_color(tokenised_line[1], line, line_nb);
	else if (!strcmp(tokenised_line[0], "C"))
		map_struct->roof_color = read_color(tokenised_line[1], line, line_nb);
	else if (!read_format_line_optional(tokenised_line, map_struct))
		err_mapfile(line_nb, line, ERR_WRONG_ID_MSG, ERR_FILE_WRONG_ID);
	destroy_array(tokenised_line);
	free (line);
}

//read the full map info in file, from the first line (in param) 
//to the first empty line after that one. store the result in map struct
//at the same time, count the number of lines.

void	read_map(char *line, int fd, t_map *map_s, int *line_nb)
{	
	char	*new_map;
	char	*old_map;

	new_map = ft_strdup("");
	while (line && !is_line_empty(line))
	{
		old_map = new_map;
		new_map = ft_strjoin(new_map, line);
		free(old_map);
		free(line);
		line = get_next_line(fd);
		*line_nb += 1;
		map_s->nb_line ++;
		if ((int) ft_strlen(line) > map_s->nb_column)
			map_s->nb_column = ft_strlen(line);
	}
	free(line);
	map_s->raw_map = ft_split(new_map, '\n');
	free(new_map);
}

void	read_cub_file(int fd, t_map *map_struct)
{
	char	*line;
	int		i;
	int		line_num;

	line = (char *) 1;
	line_num = 0;
	while (line && !map_struct->raw_map)
	{
		line = get_next_filed_line(fd, &line_num);
		line_num ++;
		i = 0;
		while (line && ft_isspace(line[i]))
			i ++;
		if (!line || line[i] == '#')
			free (line);
		else if (ft_isupcase(line[i]))
			read_format_line(line, map_struct, line_num);
		else if (char_in_set(line[i], MAP_CHAR_OK))
			read_map(line, fd, map_struct, &line_num);
		else
			err_mapfile(line_num, line, ERR_PATERN_MSG, ERR_FILE_PATERN);
	}
	line = get_next_filed_line(fd, &line_num);
	if (line)
		ft_error(MSG_MAP_LAST, ERR_MAP_LAST);
}
