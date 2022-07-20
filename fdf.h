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
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define WHITE_PIXEL 0xFFFFFF

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
	int 	x;
	int 	y;
	int 	z;
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
} t_data;

int		handle_no_event(void *data);
int		handle_keyrelease(int keysym, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		handle_mouse_release(int button, int x, int y, t_data *data);



int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

void	fdf_parsing(int fd, t_data *data);
int		number_of_lines(int fd, t_data *data);

void	update_2D_coordinates(t_array *array, double angle, t_data *data);
void	isometric_projection(t_data *data);

void	display_matrix(t_matrix A);


void	bresenham(t_array *start, t_array *end, t_img img);
void	evaluate_conditions_execute(t_array *start, t_array *end, t_img img);
void	drawing_lines(t_data *data);


char	**glob_free(char **dst);
void	free_data(t_data data);

//maybe
// void		rotation(t_array *array, t_matrix rotation);
// void		conversion_3D_to_2D(t_data *data);
// t_matrix	initialize_rotation_x_axis(double angle);
// t_matrix	initialize_rotation_y_axis(double angle);
// t_matrix	initialize_rotation_z_axis(double angle);
// t_matrix	multiply_two_matrix(t_matrix A, t_matrix B);

#endif


/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int a, int r, int g, int b);*/
