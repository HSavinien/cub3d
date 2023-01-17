/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:59:52 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/17 14:41:59 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* when reading a data line in the file, return a char** containing
 * {key , data, NULL};
 * if no data can be found, return NULL instead;
 */
char	**get_tokenised_line(char *line)
{
	int		i;
	int		start;
	char	**array;

	i = 0;
	if (!line || !line[0])
		return (NULL);
	array = ft_calloc(3, sizeof(char *));
	if (!array)
		return (ft_error(MSG_MALLOC, ERR_MALLOC));
	while (ft_isspace(line[i]))
		i ++;
	start = i;
	while (!ft_isspace(line[i]))
		i ++;
	array[0] = ft_substr(line, start, i - start);
	array[1] = ft_strtrim(line + i, " \t\n\v\f\r");
	return (array);
}

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
	int		nb_line;

	line = get_next_line(fd);
	nb_line = 1;
	while (line && is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
		nb_line ++;
	}
	if (line_num)
		line_num += nb_line;
	return (line);
}
