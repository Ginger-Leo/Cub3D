/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:06:30 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/23 15:34:44 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

/*BACKGROUND*/
int	create_bg_img(t_data *data)
{
	data->img->bg = mlx_new_image(data->mlx,
			S_WID, S_HEI);
	if (!data->img->bg)
		return (1);
	return (0);
}

/*FOREGROUND*/
int	create_fg_img(t_data *data)
{
	data->img->fg = mlx_new_image(data->mlx,
			S_WID, S_HEI);
	if (!data->img->fg)
		return (1);
	return (0);
}

/*ALL RAYS*/
int	create_ray_img(t_data *data)
{
	data->img->ray = mlx_new_image(data->mlx,
			S_WID, S_HEI);
	if (!data->img->ray)
		return (1);
	return (0);
}

/*PLAYER IMAGE*/
int	create_pl_img(t_data *data)
{
	data->img->pl = mlx_new_image(data->mlx,
			S_WID, S_HEI);
	if (!data->img->pl)
		return (1);
	return (0);
}
