/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_readfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:23:32 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/02 13:15:59 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ERR_NB_TOKEN_MSG "wrong token number : exactly two token required"
#define ERR_WRONG_ID_MSG "unknown ID token. valid ID are : [NO|SO|WE|EA|F|C]"

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i ++]))
			return (0);
	}
	return (1);
}

char	*get_next_filed_line(int fd, int *line_num)
{
	char	*line;
	char	*nb_line;

	line = get_next_line(fd);
	nb_line = 1;
	while (is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
		nb_line ++;
	}
	if (line_num)
		line_num += nb_line;
	return (line);
}

void	read_cub_file(int fd, t_map *map_struct)
{
	char	*line;
	int		i;
	int		line_num;

	line = (char *) 1;
	while (line)
	{
		line = get_next_filled_line(fd, &line_num);
		i = 0;
		while (ft_isspace(line[i]))
			i ++;
		if (ft_isupcase(line[i]))
			read_format_line(line, map_struct, line_num);
		else if (ft_isdigit(line[i]))
			read_map(line, fd, map_struct, &line_num);
		else if (line[i] == '#')
			continue ;
		else
			error_mapfile(line_num, line, ERR_LINE_MSG, ERR_FILE_PATERN);
		free(line);
	}
}

void	read_format_line(char *line, t_map *map_struct, int line_nb)
{
	char	**tokenised_line;

	tokenised_line = ft_split_word(line);
	//expected format : {"ID", "DATA", NULL}
	if (!tokenised_line[0] || !tokenised_line[1] || tokenised_line[2])
		err_mapfile(line_nb, line, ERR_NB_TOKEN_MSG, ERR_FILE_NB_TOKEN);
	else if (strcmp(tokenised_line[0], "NO"))
		*map_struct->north_path = ft_strdup(tokenised_line[1]);
	else if (strcmp(tokenised_line[0], "SO"))
		*map_struct->south_path = ft_strdup(tokenised_line[1]);
	else if (strcmp(tokenised_line[0], "WE"))
		*map_struct->west_path = ft_strdup(tokenised_line[1]);
	else if (strcmp(tokenised_line[0], "EA"))
		*map_struct->east_path = ft_strdup(tokenised_line[1]);
	else if (strcmp(tokenised_line[0], "F"))
		*map_struct->floor_color = read_color(tokenised_line[1], line, line_nb);
	else if (strcmp(tokenised_line[0], "C"))
		*map_struct->roof_color = read_color(tokenised_line[1], line, line_nb);
	else
		err_mapfile(line_nb, line, ERR_WRONG_ID_MSG, ERR_FILE_WRONG_ID);
	destroy_array(tokenised_line);
}

void	read_map(char *first_line, int fd, t_map *map_struct, int *line_nb)
{
	char		*line;
	char		*singlestr_map;
	char		*new_singlestr_map;
	int			line_len;

	line = first_line;
	singlestr_map = NULL;
	while (!is_line_empty(line) && line)
	{
		line_len = ft_strlen(line);
		if (line_len > map_struct->nb_column)
			map_struct->nb_column = line_len;
		free(line);
		line = get_next_line(fd);
		new_singlestr_map = ft_strjoin(singlestr_map, line);
		free (singlestr_map);
		singlestr_map = new_singlestr_map;
		*line_nb ++;
		map_struct->nb_line ++;
	}
	map_struct->raw_map = ft_split(singlestr_map, '\n');
}
