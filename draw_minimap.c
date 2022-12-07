#include "cub3d.h"
#include "chloutils.h"

void	draw_square(t_img *map, int x, int y, int color)
{
	int	i;
	int	j;

	x *= TILE_SMM;
	y *= TILE_SMM;
	i = 0;
	while (i < (TILE_SMM))
	{
		j = 0;
		while (j < (TILE_SMM))
		{
			map->data[TO_COORDMM((j + y), (i + x))]  = color;
			j++;
		}
		i++;
	}
}

void	draw_filledcircle(t_img *map, int x, int y)
{
	int	i;
	int r2;
	int rr;
	int tx;
	int ty;
	
	r2 = pow((TILE_SMM / 2) , 2);
	rr = (TILE_SMM / 2) << 1;
	i = 0;
	while (i < (r2 << 2))
	{
		tx = (i % rr) - (TILE_SMM / 2);
    	ty = (i / rr) - (TILE_SMM / 2);
		if (tx * tx + ty * ty <= (rr + rr))
		{	
			if ((x * TILE_SMM + (TILE_SMM / 2)) < IMG_WIDTH &&
				(y * TILE_SMM + (TILE_SMM / 2)) < IMG_HEIGHT)
				{
					map->data[TO_COORDMM((tx + (x * TILE_SMM + (TILE_SMM / 2))),
						(ty + (y * TILE_SMM + (TILE_SMM / 2))))] = 0xFF0000;
				}
		}
		i++ ;
	}
}

void	do_tile_conv(t_point *pt)
{
	pt->x *= TILE_SMM;
	pt->y *= TILE_SMM;	
}

void	draw_line(t_mlx *mlx, t_point player, t_point dir)
{
	t_point	delta;
	double	step;

	delta.x = dir.x - player.x;
	delta.y = dir.y - player.y;
	if (fabs(delta.x) > fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.x = delta.x / step;
	delta.y = delta.y / step;
	while ((player.x < IMG_WIDTH && player.y < IMG_HEIGHT
		&& player.x> 0.0 && player.y > 0.0))
	{
		if (mlx->map_s->parsed_map[(int)player.y / TILE_SMM]
			[(int)player.x / TILE_SMM] == 1)
			break ;
		mlx->minimap.data[TO_COORDMM(player.x, player.y)] = 0xFF00FF;
		// -526344 goes from white to black
		player.x += delta.x;
		player.y += delta.y;
	}
}

void	draw_figures(t_mlx *mlx, int i, int j)
{
	t_point	dir_pt;
	t_point player;

	dir_pt.x = (cos(mlx->player.direction)) + mlx->player.pos_x;
	dir_pt.y = (sin(mlx->player.direction)) + mlx->player.pos_y;
	player = (t_point){mlx->player.pos_x, mlx->player.pos_y};
	if (mlx->map_s->parsed_map[i][j] == 1)
		draw_square(&mlx->minimap, i, j, 0xFFFFFF);
	else if (mlx->map_s->parsed_map[i][j] != 1 && i != mlx->player.pos_y &&
		j != mlx->player.pos_x)
		draw_square(&mlx->minimap, i, j, 0);
	draw_filledcircle(&mlx->minimap, player.x, player.y);
	do_tile_conv(&dir_pt);
	do_tile_conv(&player);
	draw_line(mlx, player, dir_pt);
}

void	draw_minimap(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (i < (IMG_HEIGHT / (TILE_SMM)))
	{
		j = 0;
		while (j < (IMG_WIDTH / (TILE_SMM)))
		{
			if (mlx->map_s->parsed_map[i][j] == 1
				|| mlx->map_s->parsed_map[i][j] == 0)
				draw_figures(mlx, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		20, ((WIN_HEIGHT - IMG_HEIGHT) - 20));
}
