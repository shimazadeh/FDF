/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:15:38 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/06 14:15:39 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdlib.h>
#include <stdio.h>

#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "get_next_line.h"
#include "Libft/libft.h"
#include "printf/ft_printf.h"


# define MLX_ERROR 1
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define WHITE_PIXEL 0xFFFFFF
# define BLUE_PIXEL 0x0000FF

#define XK_Left                          0xff51  /* Move left, left arrow */
#define XK_Up                            0xff52  /* Move up, up arrow */
#define XK_Right                         0xff53  /* Move right, right arrow */
#define XK_Down                          0xff54  /* Move down, down arrow */


typedef struct	s_img {
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_img;

typedef struct s_matrix{
	int 	rows;
	int 	columns;
	double 	**data;
}t_matrix;

typedef struct s_array{
	double 	x;
	double 	y;
	double 	z;
	int		color;

	int 	x_screen;
	int 	y_screen;
	int		max_color;

}t_array;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_array	**array;//a table with the size
	t_img	img;

	int		width;
	int		length;

	double	scale;
	double	z_scale;
	double	zoom;

	double	roll;
	double	pitch;
	double	yaw;
} t_data;

int			ft_atoi_base(char *str, char *base);
void		put_to_upper(char *str);

int			handle_no_event(void *data);
int			handle_keyrelease(int keysym, t_data *data);
int			handle_keypress(int keysym, t_data *data);
int			handle_mouse_release(int button, int x, int y, t_data *data);
int			close_window(t_data *data);
int			handle_no_event(void *data);



void		create_data_structure(int fd, t_data *data);
void		set_map_values(t_data *data, t_array *array, char **tab, int y);
int			number_of_lines(int fd, t_data *data);
int			encode_rgb(u_int8_t red, u_int8_t green, u_int8_t blue);

void		update_2D_coordinates(t_array *array, double angle, t_data *data);
void		isometric_projection(t_data *data, double angle);


void		img_pix_put(t_img *img, int x, int y, int color);
int			draw_background(t_data *data);
int			draw(t_data *data);
void		execute(t_array *start, t_array *end, t_img img);
void		drawline(t_array *start, t_array *end, t_img img);
void		re_draw(t_data *data, int keysym);

void		rotate(t_data *data);
void		rotate_point(t_array *array, t_matrix rotation);

void		zoom(t_data *data, double zoom);
void		scale_z(t_data *data, double scale);

int			rendering(t_data data);


void		perspective(t_array *array, double angle, t_data *data);



t_matrix	multiply_two_matrix(t_matrix A, t_matrix B);
t_matrix	initialize_rotation_z_axis(double angle);
t_matrix	initialize_rotation_y_axis(double angle);
t_matrix	initialize_rotation_x_axis(double angle);
t_matrix	initialize_rotation(double roll, double pitch, double yaw);

t_matrix	initialize_translation(double tx, double ty);
void		translate(t_array *array, t_matrix translation);
void	translate_data(t_data *data, int translate, int flag);
void		display_matrix(t_matrix A);


char	**glob_free(char **dst);
void	free_data(t_data data);
void	free_matrix(t_matrix A);

#endif


/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int a, int r, int g, int b);*/
