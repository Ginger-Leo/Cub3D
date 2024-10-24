/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/23 15:35:24 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

// static void mouse_catcher(double xpos, double ypos, void* param)
// {
//     t_data *data = (t_data *)param;

// 	(void) ypos;
//     // Adjust the player's angle (horizontal rotation)
//     data->p_a += xpos * 0.001;//MOUSE_SENSITIVITY

   
//     if (data->p_a < 0)
//         data->p_a += 2 * M_PI;
// 	if (data->p_a > 2 * M_PI)
//         data->p_a -= 2 * M_PI;

//     // Optionally redraw the view or FOV
// 	build_map(data);
// 	mlx_delete_image(data->mlx, data->img->ray);
// 	create_ray_img(data);
//     draw_fov(data);  // Call your raycasting function here
// }

/*Detects key press and conducts respective actions related to the
  key pressed.*/
static void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_up(data);
		if (keydata.key == MLX_KEY_A)
			move_left(data);
		if (keydata.key == MLX_KEY_S)
			move_down(data);
		if (keydata.key == MLX_KEY_D)
			move_right(data);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_left(data);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_right(data);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
}

static uint32_t convert_rgb_to_hex(long *rgb)
{
    uint32_t	hex_value;

    // Combine the RGB components into a single hex value, with alpha set to 255 (0xFF)
    hex_value = (rgb[0] << 24) |  // Red (shifted to the highest byte)
                (rgb[1] << 16) |  // Green (shifted to the second byte)
                (rgb[2] << 8)  |  // Blue (shifted to the third byte)
                0xFF;             // Alpha channel (fully opaque)

    return (hex_value);
}

static void	fill_main_screen(t_data *data)
{
	float y;
	float x;

	y = -1;
	x = -1;
	while (++y < S_HEI / 2)
	{
		x = -1;
		while (++x < S_WID)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->ceiling));
	}
	y--;
	while (++y < S_HEI)
	{
		x = -1;
		while (++x < S_WID)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->floor));
	}
	mlx_image_to_window(data->mlx, data->img->bg, 0, 0);
}

void calc_mini_map_scaling(t_data *data)
{
    int PX_x = 0;
    int PX_y = 0;

    PX_x = S_WID / data->width / MM_SIZE;
    PX_y = S_HEI / data->height / MM_SIZE;
    if (PX_x < PX_y)
		data->PX = PX_x;
	else
		data->PX = PX_y;
}

int	mlx_functions(t_data *data)
{
	if (create_bg_img(data))
		return (1);
	fill_main_screen(data);
	calc_mini_map_scaling(data);
	if (get_textures(data))
		return (1);
	if (get_images(data))
		return (1);
	if (create_ray_img(data))
		return (1);
	if (create_pl_img(data))
		return (1);
	if (data->img->fg)
		mlx_delete_image(data->mlx, data->img->pl);
	if (create_fg_img(data))
		return (1);
	check_init_pl_angle(data);
	draw_fov_3d(data);
	draw_fov(data);
	build_map(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	// mlx_cursor_hook(data->mlx, &mouse_catcher, data);
	mlx_loop(data->mlx);
	return (0);
}
