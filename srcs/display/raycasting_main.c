/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:09:58 by tmongell          #+#    #+#             */
/*   Updated: 2022/12/18 14:52:59 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define NORTH_FACE 1
#define SOUTH_FACE 2
#define EAST_FACE 3
#define WEST_FACE 4

/* function that check if the ray coordinate are against a wall.
 * if it is against a wall, it fill the data structure and return 1.
 * else, it return 0;
 */
int	check_wall(t_coord ray, t_map *map, t_wall_data *data, t_entity *player)
{
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	//if we are on a vertical axis, check left and right
		//check case (int)y ; x-1 (only if x >=1)
		//check case (int)y ; x
	//if we are on an horizontal axis, check above and bellow
		//check case y-1 ; (int) x (only if y >=1)
		//check case y ; (int) x
		
	if (ray.x - floor(ray.x) <= EPSILON) //case left and right to check
	{
		//dprintf(2, "checking along vertical axis\n");//DEBUG
		if (ray.x >= 1 && map->parsed_map[abs((int)ray.y)][(int)ray.x-1] == WALL)
			return (wall_info(data, ray, EAST_FACE, player));//found left wall -> east texture
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL)
			return (wall_info(data, ray, WEST_FACE,player));//found right wall -> west texture
	}
	if (ray.y - floor(ray.y) <= EPSILON)
	{
		//dprintf(2, "checking along horizontal axis\n");//DEBUG
		if (ray.y >= 1 && map->parsed_map[abs((int)ray.y - 1)][(int)ray.x] == WALL) {
			//dprintf(2, "check botom\n");//DEBUG
			return (wall_info(data, ray, NORTH_FACE,player));//found botom wall -> north texture
		}
		else if (map->parsed_map[abs((int)ray.y)][(int)ray.x] == WALL) {
			//dprintf(2, "check top\n");//DEBUG
			return (wall_info(data, ray, SOUTH_FACE,player));//found top wall -> south texture
		}
	}
	//dprintf(2, "no wall found\n");//DEBUG
	return (0);
}

void	find_wall(double angle, t_wall_data *data, t_entity *player, t_map *map)
{
	//dprintf(2, "entering %s (%s:%d)\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	t_coord	ray;
	double	slope;
	double	offset;
	int nb_jmp = 0;//DEBUG
	//get ray_equation (form y=ax+b)
		// with a=tan(angle) ; b = player_y - a * player_x
	slope = tan(angle);
	offset = player->pos_y - slope * player->pos_x;
	//dprintf(2, "calculated line y = %f x + %f\n", slope, offset);//DEBUG
	//init ray position;
	ray.x = player->pos_x;
	ray.y = player->pos_y;
	//dprintf(2, "inited position\n");//DEBUG
	//while no wall found and didn't left map area
	while (!check_wall(ray, map, data, player) && nb_jmp ++ < 10) {
		//dprintf(2, "\033[1mloop : ray at %f;%f. advancing...\033[0m\n",ray.x, ray.y);//DEBUG
		get_next_pos(&ray, player->direction, slope, offset);
	}
}

void	cast_ray(double angle, int ray_num, t_img *screen, t_mlx *mlx)
{
	//dprintf(2, "\033[33mentering %s (%s:%d)\033[0m\n", __FUNCTION__, __FILE__,__LINE__);//DEBUG
	t_wall_data	wall_s;

	//find next wall
	find_wall(angle, &wall_s, &mlx->player, mlx->map_s);
	//use trigo/pythagore to calculate 'straight' distance (anti fish eye)
	//dprintf(2, "ray %d found wall at %f\n", ray_num, wall_s.distance);//DEBUG
//	wall_s.distance *= cos(angle - mlx->player.direction);
	//calculate wall height
	wall_s.height = WALL_H / (wall_s.distance * DEPTH);
	//dprintf(2, "apparent height : %f\n", wall_s.height);//DEBUG
	//if jump is implemented, it goes there--------------------------------------JUMP
	//fill image with pixel column;
	draw_wall(ray_num, wall_s, screen);
}

void	raycasting_start(t_mlx *mlx, t_img *screen)
{
	int		i;
	double	ray_angles[WIN_W];	//list the angle of each ray, in rad


	//calculate the angle of each ray
	get_ray_angle(mlx, ray_angles);
	i = 0;
	while (i < WIN_W)
	{
		cast_ray(ray_angles[i], i, screen, mlx);
		i ++;
	}
}
