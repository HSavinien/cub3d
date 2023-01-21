/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:45:00 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/21 12:15:13 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_point(t_ncomp c, t_ncomp i)
{
	t_ncomp	z;
	t_ncomp	zsqrt;
	int		count;

	(void)i;
	z.re = 0;
	z.im = 0;
	zsqrt.re = z.re * z.re;
	zsqrt.im = z.im * z.im;
	count = 0;
	while ((zsqrt.re + zsqrt.im < 4) && (count < ITERATIONS))
	{
		z.im = 2 * z.re * z.im + c.im;
		z.re = zsqrt.re - zsqrt.im + c.re;
		zsqrt.re = pow(z.re, 2);
		zsqrt.im = pow(z.im, 2);
		count++;
	}
	return (count);
}

int	julia_point(t_ncomp z, t_ncomp c)
{
	t_ncomp		zsqrt;
	int			count;

	zsqrt.re = z.re * z.re;
	zsqrt.im = z.im * z.im;
	count = 0;
	while ((zsqrt.re + zsqrt.im < 4) && (count < ITERATIONS))
	{
		z.im = 2 * z.re * z.im + c.im;
		z.re = zsqrt.re - zsqrt.im + c.re;
		zsqrt.re = pow(z.re, 2);
		zsqrt.im = pow(z.im, 2);
		count++;
	}
	return (count);
}

int	tricorn_point(t_ncomp c, t_ncomp i)
{
	t_ncomp	z;
	t_ncomp	zsqrt;
	int		count;

	(void)i;
	z.re = 0;
	z.im = 0;
	zsqrt.re = z.re * z.re;
	zsqrt.im = z.im * z.im;
	count = 0;
	while ((zsqrt.re + zsqrt.im < 4) && (count < ITERATIONS))
	{
		z.im = -2 * z.re * z.im + c.im;
		z.re = zsqrt.re - zsqrt.im + c.re;
		zsqrt.re = pow(z.re, 2);
		zsqrt.im = pow(z.im, 2);
		count++;
	}
	return (count);
}
