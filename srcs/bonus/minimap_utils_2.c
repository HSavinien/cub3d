/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:29:03 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/18 19:52:27 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <movement.h>

int	map_line(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m, bool end)
{
	t_pt_map	draw_p;

	draw_p.i = mini_m->i + raw_p->i;
	draw_p.j = mini_m->j + raw_p->j;
	if ((draw_p.i) < mlx->map_s->nb_line && (draw_p.j) < mlx->map_s->nb_column
		&& end == false && mlx->map_s->raw_map[draw_p.i][draw_p.j] != '\0')
		draw_figures(mlx, *mini_m, draw_p);
	else
		end = true;
	if (end == true && (mini_m->j < MM_W || mini_m->i < MM_H))
		draw_square(mlx, mini_m->i, mini_m->j, 0x80000000);
	return (end);
}

bool	is_inside(double cx, double cy, t_point check, int r)
{
	if ((check.x - cx) * (check.x - cx) + (check.y - cy)
		* (check.y - cy) <= r * r)
		return (true);
	else
		return (false);
}

void	draw_rev_circle(t_mlx *mlx, double cx, double cy, int r)
{
	t_point	check;

	check = (t_point){0, 0};
	while (check.y < MM_W * TILE_SMM)
	{
		check.x = 0;
		while (check.x < MM_W * TILE_SMM)
		{
			if (is_inside(cx, cy, check, r) == false)
			{	
				mlx->minimap.data[(int)(check.y) *(MM_W * TILE_SMM)
					+ (int)(check.x)] = 0xFF000000;
			}
			check.x++;
		}
		check.y++;
	}
}
