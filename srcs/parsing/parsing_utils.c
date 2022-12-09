/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:59:52 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/05 21:04:32 by tmongell         ###   ########.fr       */
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
	int 	start;
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
