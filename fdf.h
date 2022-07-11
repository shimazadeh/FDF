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
#include "get_next_line.h"
#include "Libft/libft.h"
#include "printf/ft_printf.h"


# define MLX_ERROR 1
# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300

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

typedef struct s_array{
	int x;
	int y;
	int z;
	char	*color;

	int x_screen;
	int y_screen;
} t_array;

typedef	struct	s_rect {
	int x; //coordinate of origin
	int y; //coordinate of origin
	int width;
	int height;
	int color;
}t_rect;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_array	**array;//a table with the size
	t_img	img;
} t_data;

int	handle_no_event(void *data);
int	handle_keyrelease(int keysym, t_data *data);
int	handle_keypress(int keysym, t_data *data);
int render(t_data *data);



#endif


/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int a, int r, int g, int b);*/
