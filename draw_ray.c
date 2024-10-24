/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/23 15:36:07 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Draws single ray from player's direction until wall. PXP/2 used
  in order to center ray onto the player. 'cos' and '-sin' set ray
  direction based on player's agnle. '-sin' as Y-axis inverted*/
static void	draw_single_ray(t_data *data, float angle, int color)
{
	float	x;
	float	y;
	float	mag;

	x = (data->x_p * data->PX) + (data->pl_size / 2);
	y = (data->y_p * data->PX) + (data->pl_size / 2);
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * RAY_SPEED * data->PX);
		y += (data->ray_dir_y * RAY_SPEED * data->PX);
		if (x < 0 || y < 0 || x >= data->width * data->PX || y >= data->height * data->PX
			|| data->map[(int)y / (int)data->PX][(int)x / (int)data->PX] == '1')
			break ;
		mlx_put_pixel(data->img->ray, x, y, color);
	}
}

void	draw_fov(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	current_angle;
	float	step_angle;

	data->ray_index = 0;
	start_angle = data->p_a - PI / 6;
	end_angle = data->p_a + PI / 6;
	step_angle = (end_angle - start_angle) / MM_RAYS;
	current_angle = start_angle;
	data->img->colour = 0xFF0000FF;
	while (current_angle <= end_angle)
	{
		draw_single_ray(data, current_angle, data->img->colour);
		current_angle += step_angle;
		data->ray_index++;
		if (data->img->colour == 0xFF0000FF)
			data->img->colour = 0x00FF00FF;
		else if (data->img->colour == 0x00FF00FF)
			data->img->colour = 0x0000FFFF;
		else
			data->img->colour = 0xFF0000FF;
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}

/*functions for casting single, individual rays used for '3D' rendering*/

static float	draw_single_ray_3d(t_data *data, float angle)
{
	float	x;
	float	y;
	float	mag;
	float	len;

	x = data->x_p;
	y = data->y_p;
	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	mag = sqrt(data->ray_dir_x * data->ray_dir_x
			+ data->ray_dir_y * data->ray_dir_y);
	data->ray_dir_x /= mag;
	data->ray_dir_y /= mag;
	while (1)
	{
		x += (data->ray_dir_x * RAY_SPEED);
		y += (data->ray_dir_y * RAY_SPEED);
		len = sqrt((x - data->x_p) * (x - data->x_p) + (y - data->y_p) * (y - data->y_p));

		if (x < 0 || y < 0 || x >= S_WID || y >= S_HEI
			|| data->map[(int)y][(int)x] == '1')
			return (len);
	}
}
static void init_step_side(float *side_dist_x, float *side_dist_y, int *step_x, int *step_y, t_data *data, int map_x, int map_y, float x, float y, float delta_dist_x, float delta_dist_y)
{
	*step_x = data->ray_dir_x < 0 ? -1 : 1;
	*side_dist_x = (*step_x == -1) ? (x - map_x) * delta_dist_x : (map_x + 1.0 - x) * delta_dist_x;
	*step_y = data->ray_dir_y < 0 ? -1 : 1;
	*side_dist_y = (*step_y == -1) ? (y - map_y) * delta_dist_y : (map_y + 1.0 - y) * delta_dist_y;
}

static int perform_dda(t_data *data, int *map_x, int *map_y, float *side_dist_x, float *side_dist_y, float delta_dist_x, float delta_dist_y)
{
	int side;

	while (1)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += delta_dist_x;
			*map_x += (data->ray_dir_x < 0) ? -1 : 1;
			side = 0;
		}
		else
		{
			*side_dist_y += delta_dist_y;
			*map_y += (data->ray_dir_y < 0) ? -1 : 1;
			side = 1;
		}
		if (data->map[*map_y][*map_x] == '1')
			return (side);
	}
}

static int determine_hit_direction(t_data *data, int side)
{
	if (side == 0) // Vertical (East-West)
		return (data->ray_dir_x > 0 ? 2 : 3);
	else // Horizontal (North-South)
		return (data->ray_dir_y > 0 ? 4 : 1);
}

static int hit_direction(t_data *data, float angle)
{
	float x = data->x_p, y = data->y_p;
	int map_x = (int)x, map_y = (int)y;
	float delta_dist_x = fabs(1 / data->ray_dir_x), delta_dist_y = fabs(1 / data->ray_dir_y);
	float side_dist_x, side_dist_y;
	int step_x, step_y;

	data->ray_dir_x = cos(angle);
	data->ray_dir_y = -sin(angle);
	init_step_side(&side_dist_x, &side_dist_y, &step_x, &step_y, data, map_x, map_y, x, y, delta_dist_x, delta_dist_y);

	int side = perform_dda(data, &map_x, &map_y, &side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y);
	return (determine_hit_direction(data, side));
}

static void	updating_fg(t_data *data) //ORGINAL
{
	int		ray_index;
	float	len;
	float	line_height;
	float	start_y;
	float	end_y;
	float	y;
	float	screen_center;
	int		pixel_x;
	float	angle_offset;
	float	fov = PI / 3;
 
	screen_center = S_HEI / 2;
	ray_index = 0;
	angle_offset = (ray_index - RAYS / 2) * (fov / RAYS);

	while (ray_index < RAYS)
    {
        len = data->img->len[ray_index];
        if (len == 0)
            len = 0.01f;
		len = len * cos(angle_offset);
        line_height = (B_HEI) / len;
        start_y = screen_center - (line_height / 2);
        end_y = screen_center + (line_height / 2);
        y = start_y;
        pixel_x = S_WID - (ray_index * (S_WID / (float)RAYS));
        while (y <= end_y)
        {
            if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 1)
                mlx_put_pixel(data->img->fg, pixel_x, y, 0x00FFFFFF);
            if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 2)
                mlx_put_pixel(data->img->fg, pixel_x, y, 0xFF00FFFF);
            if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 3)
                mlx_put_pixel(data->img->fg, pixel_x, y, 0xFFFF00FF);
            if (y >= 0 && y < S_HEI && data->img->hit_dir[ray_index] == 4)
                mlx_put_pixel(data->img->fg, pixel_x, y, 0x000000FF);
            y += 1;
        }
        ray_index++;
    }
	mlx_image_to_window(data->mlx, data->img->fg, 0, 0);	
}


/*functions for casting a series of rays used for '3D' rendering*/

void	draw_fov_3d(t_data *data)
{
	float	start_angle;
	float	end_angle;
	float	current_angle;
	float	step_angle;
	int		i;

	
	start_angle = data->p_a - PI / 6;
	end_angle = data->p_a + PI / 6;
	step_angle = (end_angle - start_angle) / RAYS;
	current_angle = start_angle;
	i = 0;
	while (current_angle <= end_angle && i < RAYS)
	{
		data->img->len[i] = draw_single_ray_3d(data, current_angle);
		data->img->hit_dir[i] = hit_direction(data, current_angle);
		current_angle += step_angle;
		i++;
	}
	updating_fg(data);
	// clean exit
}



