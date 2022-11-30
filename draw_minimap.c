#include "cub3d.h"

void	draw_square(t_img *map, int x, int y, int color)
{
	int	i;
	int	j;

	x *= TILE_SMM;
	y *= TILE_SMM;
	i = 0;
	while (i < TILE_SMM)
	{
		j = 0;
		while (j < TILE_SMM)
		{
			map->data[TO_COORD((j + y), (i + x))]  = color;
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
			map->data[TO_COORD((tx + (x * TILE_SMM + r)), (ty + (y * TILE_SMM + r)))] = 0xFF0000;
		i++ ;
	}
}

/*void	draw_filledtriangle(t_img *map, int x, int y, t_vector dir)
{
	
}*/
void	draw_line(t_img *map, double x1, double y1, double x2, double y2)
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
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		map->data[TO_COORD(x1, y1)] = 0xFFFFFF; // apparently the problem is here
		// -526344 goes from white to black
		x1 += deltaX;
		y1 += deltaY;
	}
}

void	draw_figures(t_mlx *mlx, int i, int j)
{
	double	x;
	double	y;
	double	tile;

	tile = TILE_SMM + 4;
	x = mlx->player.pos_x * tile + mlx->player.dir_x;
	y = mlx->player.pos_y * tile + mlx->player.dir_y;
	if (mlx->map_s->parsed_map[i][j] == 1)
		draw_square(&mlx->minimap, i, j, 0xFFFFFF);
	else if (mlx->map_s->parsed_map[i][j] != 1 && i != mlx->player.pos_y && j != mlx->player.pos_x)
		draw_square(&mlx->minimap, i, j, 0);
	draw_filledcircle(&mlx->minimap, mlx->player.pos_x, mlx->player.pos_y);
	//draw_line(&mlx->minimap, mlx->player.pos_x * tile, mlx->player.pos_y, x, y); 
}