/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:40:26 by mmeier            #+#    #+#             */
/*   Updated: 2024/10/09 12:11:46 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*Rotates player counter-clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_left(t_data *data)
{
	data->p_a += ro_speed;
	if (data->p_a >= 2 * PI)
		data->p_a -= 2 * PI;
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	create_ray_img(data);
	draw_line(data);
}

/*Rotates player clockwise. If statement, in order
  to keep the angle within 0 and 360 degrees (2*PI).*/
void	rotate_right(t_data *data)
{
	data->p_a -= ro_speed;
	if (data->p_a < 0)
		data->p_a += 2 * PI;
	build_map(data);
	mlx_delete_image(data->mlx, data->img->ray);
	create_ray_img(data);
	draw_line(data);
}
