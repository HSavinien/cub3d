/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:38:34 by tmongell          #+#    #+#             */
/*   Updated: 2023/01/04 17:48:22 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*----------------------------------------------------------------------------/*
 * the function in this file aime to facilitate the use of mlx_string_put
 * notably for numeric values styles object
 *
 *		/!\ - FUNCTION ARE NOT FINISHED, FILE SHOULD NOT COMPILE - /!\
 *
 */

#define TXT_COLOR 0xFA0F0F

int	mlx_putnbr(int pos_x, int pos_y, int nbr, t_mlx *mlx)
{
	int	cursor;

	cursor = pos_x;
	if (nbr < 0)
	{
		nbr *=-1;
		mlx_put_string(mlx->mlx_ptr, mlx->win_ptr, cursor ++, pos_y,
			TXT_COLOR, "-");
	}

}

int	mlx_putfloat(int pos_x, int pos_y, double nbr, t_mlx *mlx)
{
	int	cursor;

	cursor = mlx_putnbr(pos_x, pos_y, (int)nbr, mlx);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, pos_x + cursor++, pos_y,
			TXT_COLOR, ".");
	while (floor(nbr) != nbr)
		nbr *= 10;
	cursor += mlx_putnbr(pos_x + cursor, pos_y, (int)fabs(nbr), mlx)
}
