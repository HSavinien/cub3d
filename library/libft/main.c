/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:07:30 by tmongell          #+#    #+#             */
/*   Updated: 2022/11/05 01:17:26 by tmongell         ###   ########.fr       */
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
#include "libft.h"

int	main(int ac, char **av)
{
	int		i = 0;
	char	**result;
	if (ac < 3)
		return(printf("error args\nusage : <%s> <string> <sep>\n", av[0]));
	result = ft_split(av[1], av[2][0]);
	while (result[i])
		printf("%s\n", result[i++]);
}
