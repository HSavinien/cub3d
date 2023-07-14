/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:30:00 by cmaroude          #+#    #+#             */
/*   Updated: 2023/06/28 16:35:03 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	psychedelic(double phase, int count)
{
	int	r;
	int	g;
	int	b;

	r = sin(0.08 * count + 2 + phase) * 128 + 127;
	g = sin(0.08 * count + 0 + phase) * 128 + 127;
	b = sin(0.08 * count + 4 + phase) * 128 + 127;
	return (0 << 24 | r << 16 | g << 8 | b | BACKGROUND_TR << 24);
}

int	couleur_pixel(double phase, int count)
{
	if (count < ITERATIONS)
		return (psychedelic(phase, count));
	else
		return (0);
}
