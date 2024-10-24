/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstorey <lstorey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:58 by lstorey           #+#    #+#             */
/*   Updated: 2024/10/23 15:36:07 by lstorey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./includes/libft/libft.h"
# include "./includes/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

# define STEPS 0.3
# define RAY_SPEED 0.03
# define RO_SPEED 0.3
# define PI 3.1415926535
# define MM_RAYS 20
# define RAYS 1500
# define S_WID 1260
# define S_HEI 1260  // always determined by screen_width
# define MM_SIZE 4 // downscale factor for mini map and player
# define B_HEI 630
typedef struct s_data	t_data;
typedef struct s_img
{
	t_data			*data;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	long int		floor[3];
	long int		ceiling[3];
	float			len[RAYS];
	int				hit_dir[RAYS];
	mlx_image_t		*wl;
	mlx_image_t		*fl;
	mlx_image_t		*pl;
	mlx_image_t		*ray;
	mlx_image_t		*bg;
	mlx_image_t		*fg;
	mlx_image_t		*bg_ray;
	unsigned int	colour;
}	t_img;

typedef struct s_pl
{
	int				x_strt;
	int				y_strt;
	int				pix_x;
	int				pix_y;
	double			x_centr;
	double			y_centr;
	double			ro_x;
	double			ro_y;
	double			transl_x;
	double			transl_y;
	int				fnl_x;
	int				fnl_y;
	
} t_pl;

typedef struct s_txtr
{
	mlx_texture_t	*wl;
	mlx_texture_t	*fl;
	mlx_texture_t	*pl;
}	t_txtr;

typedef struct s_data
{
	char			**map;
	char			**clone_map;
	char			*file_cnt;
	char			**file_arr;
	int				wall_check;
	mlx_t			*mlx;
	char			p_dir;
	float			x_p;
	float			y_p;
	float			ray_dir_x;
	float			ray_dir_y;
	int				height;
	int				width;
	int				parsing_ok;
	float			p_dx; // player delta x
	float			p_dy; // player delta y
	float			p_a; // player angle
	double			hor_next_y;
	double			hor_next_x;
	double			hor_delta_y;
	double			hor_delta_x;
	float			len_close_hor;
	int				up;
	float			ray_dist;
	float			line_height;
	int				ray_index;
	float			PX; // size of mini_map tiles
	float			pl_size;
	mlx_image_t		*main_screen;
	t_txtr			*txtr;
	t_img			*img;
}	t_data;

/*						core_functions.c						*/

int			cube_it(char *av, t_data *data);

/*						utils.c									*/

int			err_msg(int err_flag);
int			arr_splitter(t_data *data);
long int	ft_atol(const char *str);
char		*ft_read_map(int fd);

/*						utils_2.c								*/

int			number_count(char *str);
void		check_init_pl_angle(t_data *data);
void		official_exit(void);

/*						mlx_functions.c							*/

int			mlx_functions(t_data *data);

/*						map_checking_a.c						*/

int			map_checker(t_data *data);	

/*						map_checking_b.c						*/

int			check_double_n(t_data *data);

/*						free_a.c								*/

int			free_all(t_data *data, int return_val);
int			free_input(t_data *data);
int			free_dir(t_img *img);
void		delete_textures(t_data *data);
void		delete_images(t_data *data);

/*						free_b.c								*/

void		free_arr(char ***arr);
void		free_str(char **str);
char		**free_arr_rev(char ***av, int i);
void		del_txtr_only(t_data *data);
void		del_img_only(t_data *data);

/*						texture_info.c							*/

int			texture_extract(t_data *data, t_img *img, int x, int y);

/*						texture_info_utils.c					*/

int			get_north(char *address, t_img *img);
int			get_south(char *address, t_img *img);
int			get_east(char *address, t_img *img);
int			get_west(char *address, t_img *img);
int			range_check(long int *arr);

/*						flood_fill.c							*/

int			no_closed_walls(t_data *data);
int			count_lines_arr(char **arr);

/*						map_utils.c								*/

int			map_extract(t_data *data);

/*						moves.c									*/

void		move_up(t_data *data);
void		move_left(t_data *data);
void		move_down(t_data *data);
void		move_right(t_data *data);

/*						draw_ray.c								*/

void		draw_fov(t_data *data);
void		draw_fov_3d(t_data *data);

/*						init_images.c							*/

int			create_ray_img(t_data *data);
int			create_pl_img(t_data *data);
int			create_bg_img(t_data *data);
int			create_fg_img(t_data *data);

/*						rotate.c								*/

void		rotate_left(t_data *data);
void		rotate_right(t_data *data);

/*						build_mini_map.c						*/

void		build_map(t_data *data);
void		draw_player(t_data *data, float width, float height);
int			get_textures(t_data *data);
int			get_images(t_data *data);

/*						utils_to_be_deleted.c					*/

void		print_arr(char **arr);
void		info_printer(t_img *img);
void		file_splitter(t_data *data);
void		map_printer(t_data *data);

#endif
