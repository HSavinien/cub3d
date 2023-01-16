/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:59:52 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/16 20:01:05 by tmongell         ###   ########.fr       */
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
	//skip spaces
	while (ft_isspace(line[i]))
		i ++;
	start = i;
	//skip not space
	while (!ft_isspace(line[i]))
		i ++;
	//dup first token into array[0]
	array[0] = ft_substr(line, start, i - start);
	//send the result of a ft_strtrim on the second part to array[2]
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
