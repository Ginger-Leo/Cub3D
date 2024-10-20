/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:36:39 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/17 11:09:47 by mmeier           ###   ########.fr       */
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
	while (++y < screen_height * PX/2)
	{
		x = -1;
		while (++x < screen_width * PX)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->ceiling));
	}
	while (++y < screen_height * PX)
	{
		x = -1;
		while (++x < screen_width * PX)
			mlx_put_pixel(data->img->bg, x, y, convert_rgb_to_hex(data->img->floor));
	}
	mlx_image_to_window(data->mlx, data->img->bg, 0, 0);
}

int	mlx_functions(t_data *data, t_img *img)
{
	(void)img;
	data->mlx = mlx_init(screen_width * PX, screen_height * PX, "cub3D", false);
	if (!data->mlx)
		return (1);
	if (create_bg_img(data))
		return (1);
	fill_main_screen(data);
	if (get_textures(data))
		return (1);
	if (get_images(data))
		return (1);
	if (create_ray_img(data))
		return (1);
	if (create_pl_img(data))
		return (1);
	check_init_pl_angle(data);
	build_map(data);
	draw_fov(data);
	mlx_key_hook(data->mlx, my_key_hook, data);
	// mlx_cursor_hook(data->mlx, &mouse_catcher, data);
	mlx_loop(data->mlx);
	return (0);
}
