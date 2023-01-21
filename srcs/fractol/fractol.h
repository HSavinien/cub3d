/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:58:27 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/21 15:41:22 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <cub3d.h>

# define STEPS	0.03
# define ITERATIONS	25

typedef struct s_ncomp {
	double	re;
	double	im;
}	t_ncomp;

typedef struct s_fractol_data {
	t_ncomp	c;
	double	phase;
	double	offx;
	double	offy;
	int		(*function)(t_ncomp c, t_ncomp i);
}	t_fractol_data;

int		mandelbrot_point(t_ncomp c, t_ncomp i);
int		couleur_pixel(double phase, int count);
int		psychedelic(double phase, int count);
int		tricorn_point(t_ncomp c, t_ncomp i);
int		julia_point(t_ncomp z, t_ncomp c);
void	move(t_fractol_data *data, int origin, float steps);
void	zoom(t_fractol_data *data, int k, double x, double y);
int		ft_julia_rotation(int x, int y, t_fractol_data *data);

#endif
