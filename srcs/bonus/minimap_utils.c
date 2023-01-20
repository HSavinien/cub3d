/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaroude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:21:40 by cmaroude          #+#    #+#             */
/*   Updated: 2023/01/20 16:11:59 by cmaroude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minimap.h>

void	do_tile_conv(t_coord *pt)
{
	pt->x *= TILE_SMM;
	pt->y *= TILE_SMM;
}

t_coord	init_delta(t_coord player, t_coord dir)
{
	t_coord	delta;
	double	step;

	delta.x = dir.x - player.x;
	delta.y = dir.y - player.y;
	if (fabs(delta.x) > fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	return (delta);
}

void	add_delta(t_coord *player, t_coord *player_org, t_coord delta)
{
	player->x += delta.x;
	player->y += delta.y;
	player_org->x += delta.x;
	player_org->y += delta.y;
}

int	get_offset(t_mlx *mlx, t_pt_map *raw_p, t_pt_map *mini_m)
{
	int			tmp;
	t_pt_map	mini;

	tmp = 0;
	mini = (t_pt_map){mini_m->i, mini_m->j};
	raw_p->i = mlx->player.pos_y - (MM_H / 2);
	if (raw_p->i < 0)
		tmp = raw_p->i;
	while (tmp++ < 0)
	{
		mini.j = 0;
		while (mini.j < MM_W)
			draw_square(mlx, mini.i, mini.j++, 0x80000000);
		mini.i++;
	}
	raw_p->j = mlx->player.pos_x - (MM_W / 2);
	if (raw_p->j <= 1)
		raw_p->j = 0;
	mini_m->i = mini.i;
	return (tmp);
}
