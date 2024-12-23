/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:40:41 by mmeier            #+#    #+#             */
/*   Updated: 2024/11/11 12:08:02 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

static int	message_helper(int n)
{
	if (n == 1)
		ft_putstr_fd("Error\nFailed to load north texture.\n", 2);
	else if (n == 2)
		ft_putstr_fd("Error\nFailed to load east texture.\n", 2);
	else if (n == 3)
		ft_putstr_fd("Error\nFailed to load south texture.\n", 2);
	else if (n == 4)
		ft_putstr_fd("Error\nFailed to load west texture.\n", 2);
	return (1);
}

/*Populates texture variables, texture struct itself is already initialised
  within init_data function.*/
int	get_textures(t_data *data)
{
	data->txtr->wl = mlx_load_png("./textures/black_wall_mini_map.png");
	if (!data->txtr->wl)
		return (1);
	data->txtr->fl = mlx_load_png("./textures/white_floor_mini_map.png");
	if (!data->txtr->fl)
		return (1);
	data->txtr->no = mlx_load_png(data->img->no);
	if (!data->txtr->no)
		return (message_helper(1));
	data->txtr->ea = mlx_load_png(data->img->ea);
	if (!data->txtr->ea)
		return (message_helper(2));
	data->txtr->so = mlx_load_png(data->img->so);
	if (!data->txtr->so)
		return (message_helper(3));
	data->txtr->we = mlx_load_png(data->img->we);
	if (!data->txtr->we)
		return (message_helper(4));
	return (0);
}

/*Populates image variables, image struct itself is already initialised
  within init_data function.*/
int	get_images(t_data *data)
{
	data->img->wl = mlx_texture_to_image(data->mlx, data->txtr->wl);
	if (!data->img->wl)
		return (1);
	data->img->fl = mlx_texture_to_image(data->mlx, data->txtr->fl);
	if (!data->img->fl)
		return (1);
	mlx_resize_image(data->img->wl, data->px, data->px);
	mlx_resize_image(data->img->fl, data->px, data->px);
	return (0);
}

/*Builds 2d map (floor, wall, player). Deletion and creation of textures
  and images needed in this function, as it is called everytime when a
  move is conducted (map gets again build "from scratch" over and over
  again).*/
void	build_map(t_data *data)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	del_img_only(data);
	get_images(data);
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			mlx_image_to_window(data->mlx, data->img->fl,
				x * data->px, y * data->px);
			if (data->map[y][x] == '1')
				mlx_image_to_window(data->mlx, data->img->wl,
					x * data->px, y * data->px);
		}
	}
	mlx_image_to_window(data->mlx, data->img->ray, 0, 0);
}
