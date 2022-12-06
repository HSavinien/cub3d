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
	int r;
	int rr;
	int tx;
	int ty;
	
	r = TILE_SMM / 2;
	r2 = pow(r , 2);
	rr = r << 1;
	i = 0;
	while (i < (r2 << 2))
	{
		tx = (i % rr) - (r);
    	ty = (i / rr) - (r);
		if (tx * tx + ty * ty <= (rr + rr))
		{	
			if ((x * TILE_SMM + r) < IMG_WIDTH &&
				(y * TILE_SMM + r) < IMG_HEIGHT)
				{
					map->data[TO_COORDMM((tx + (x * TILE_SMM + r)),
						(ty + (y * TILE_SMM + r)))] = 0xFF0000;
				}
		}
		i++ ;
	}
}

/*void	draw_filledtriangle(t_img *map, int x, int y, t_vector dir)
{
	
}*/
void	draw_line(t_mlx *mlx, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	if (fabs(deltaX) > fabs(deltaY))
		step = fabs(deltaX);
	else
		step = fabs(deltaY);
	deltaX = deltaX / step;
	deltaY = deltaY / step;
	while ((x1 < IMG_WIDTH && y1 < IMG_HEIGHT && x1 > 0.0 && y1 > 0.0))
	{
		if (mlx->map_s->parsed_map[(int)y1 / TILE_SMM][(int)x1 / TILE_SMM] == 1)
			break ;
		mlx->minimap.data[TO_COORDMM(x1, y1)] = 0xFF00FF;
		// -526344 goes from white to black
		x1 += deltaX;
		y1 += deltaY;
	}
}

void	draw_figures(t_mlx *mlx, int i, int j)
{
	double	x;
	double	y;
	double	dir;
	double	tile;
	double	r;

	dir = mlx->player.direction;
	r = (double)TILE_SMM / 2.0;
	x = (2.0 * cos(mlx->player.direction)) + mlx->player.pos_x;
	y = (2.0 * sin(mlx->player.direction)) + mlx->player.pos_y;
	tile = (TILE_SMM);
	if (mlx->map_s->parsed_map[i][j] == 1)
		draw_square(&mlx->minimap, i, j, 0xFFFFFF);
	else if (mlx->map_s->parsed_map[i][j] != 1 && i != mlx->player.pos_y &&
		j != mlx->player.pos_x)
		draw_square(&mlx->minimap, i, j, 0);
	draw_filledcircle(&mlx->minimap, mlx->player.pos_x, mlx->player.pos_y);
	draw_line(mlx, mlx->player.pos_x * tile, mlx->player.pos_y * tile,
		x * tile, y * tile);
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
			if (mlx->map_s->parsed_map[i][j] == 1 || mlx->map_s->parsed_map[i][j] == 0)
				draw_figures(mlx, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->minimap.img_ptr,
		20, ((WIN_HEIGHT - IMG_HEIGHT) - 20));
	//show_map(mlx->map_s->parsed_map);
}
