/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/23 15:28:18 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Moves player forward by 'steps' based on it's angle position 
  (cos / sin / data->p_a). Size of STEPS defined in header.
  '- sin' as Y axis decreases upwards. In case there is no wall in the player's
  new position, current location of player gets updated.*/
void	move_up(t_data *data)
{
	double	new_x;
	double	new_y;

	// new_x = data->x_p + cos(data->p_a) * STEPS;
	// new_y = data->y_p - sin(data->p_a) * STEPS;
	new_x = data->x_p + data->p_dx * STEPS;
	new_y = data->y_p - data->p_dy * STEPS;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		mlx_delete_image(data->mlx, data->img->ray);
		mlx_delete_image(data->mlx, data->img->fg);
		create_fg_img(data);
		create_ray_img(data);
		draw_fov_3d(data);
		build_map(data);
		draw_fov(data);
	}
}

/*Moves player backwards by 'steps' based on it's angle position 
  (cos / sin / data->p_a). Size of steps defined in header.
  '+ sin' as Y axis increases downwards. In case there is no wall in the player's
  new position, current location of player gets updated.*/
void	move_down(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->x_p - data->p_dx * STEPS;
	new_y = data->y_p + data->p_dy * STEPS;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		mlx_delete_image(data->mlx, data->img->ray);
		mlx_delete_image(data->mlx, data->img->fg);
		create_fg_img(data);
		create_ray_img(data);
		draw_fov_3d(data);
		build_map(data);
		draw_fov(data);
	}
}

/*Makes player strafe to left by -90 degrees in relation to
  direction facing. Strafe angle calculated by adding 90 degrees
  (PI/2) to current player angle.*/
void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;

	strafe_angle = data->p_a + PI / 2;
	new_x = data->x_p + cos(strafe_angle) * STEPS;
	new_y = data->y_p - sin(strafe_angle) * STEPS;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		mlx_delete_image(data->mlx, data->img->ray);
		mlx_delete_image(data->mlx, data->img->fg);
		create_fg_img(data);
		create_ray_img(data);
		draw_fov_3d(data);
		build_map(data);
		draw_fov(data);
	}
}

/*Makes player strafe to right by +90 degrees in relation to
  direction facing. Strafe angle calculated by substracting 90 degrees
  (PI/2) from current player angle.*/
void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;
	double	strafe_angle;

	strafe_angle = data->p_a - PI / 2;
	new_x = data->x_p + cos(strafe_angle) * STEPS;
	new_y = data->y_p - sin(strafe_angle) * STEPS;
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_p = new_x;
		data->y_p = new_y;
		mlx_delete_image(data->mlx, data->img->ray);
		mlx_delete_image(data->mlx, data->img->fg);
		create_fg_img(data);
		create_ray_img(data);
		draw_fov_3d(data);
		build_map(data);
		draw_fov(data);
	}
}
