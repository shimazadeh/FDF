/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:57:10 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/11 20:57:11 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display(t_data data, int dimensions[2])
{
	int x;
	int y;

	y = 0;
	while (y < data.length)
	{
		x = 0;
		while(x < data.width)
		{
			ft_printf("x is %d, y is %d, z is %d, color is %X in 3D\n", data.array[y][x].x, data.array[y][x].y, data.array[y][x].z, data.array[y][x].color);
			ft_printf("x is %d, y is %d in 2D\n", data.array[y][x].x_screen, data.array[y][x].y_screen);
			ft_printf("---------------------------------------------------------\n");
			x++;
		}
		y++;
	}
	return ;
}

void	convert_3D_to_2D(t_data data, int dimensions[2])
{
	int	x;
	int	y;

	y = 0;
	dimensions[0] = data.width;
	dimensions[1] = data.length;
	while (y < dimensions[1])
	{
		x = 0;
		while(x < dimensions[0])
		{
			data.array[y][x].x_screen = (data.array[y][x].x - data.array[y][x].y) * cos(0.523599) + WINDOW_WIDTH / 2;
			data.array[y][x].y_screen = (data.array[y][x].x + data.array[y][x].y) * sin(0.523599) - data.array[y][x].z + WINDOW_HEIGHT / 2;
			x++;
		}
		y++;
	}
	return ;
}
/*
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("keypress: %d\n", keysym);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bits_per_pixel - 8;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bits_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}*/

int	render_map(t_data *data)
{
	int j;
	int i;

	i = 0;
	j = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (j < data->length)
	{
		i = 0;
		while (i < data->width)
		{
			if(data->array[j][i].x_screen == i && data->array[j][i].y_screen == j)
				img_pix_put(&data->img, i, j, WHITE_PIXEL);//data.array[j][i].color);
			i++;
		}
		++j;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0 , 0);
	return (0);
}

int	main(int ac, char **ag)
{
	int 	fd;
	t_data	data;
	int		dimensions[2];

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
			return (ft_printf("error opening the map\n"), -1);
		ft_printf("the value of fd is %d\n", fd);
	}
	else
		return (ft_printf("invalid number of arguments\n"), -1);
	if (number_of_lines(fd, dimensions) < 0)
		return (-1);
	ft_printf("width is %d, length is %d\n", dimensions[0], dimensions[1]);

	fd = open(ag[1], O_RDONLY);
/****parsing and converting the dimensions****/
	data = fdf_parsing(fd, dimensions);
	convert_3D_to_2D(data, dimensions);
	display(data, dimensions);


/****printing the points****/
/*	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render_map, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);
//	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);*/
//	free_data(data, dimensions);
	return (0);
}


/*step1: read the file line by line using get_next_line
			 parse each line (if its not integer print a message and exit)
			 store the values as an array which is part of the structure? (x, y, z, color)
			 checks:
			 	some numbers include a specific color separated by comma (,)
				the length of all rows must be equal to each other
			store the dimension of the map

	  step2:
			use the structure created previously to draw each point
			connect the points using the bresenham algorithm

array = two dimensional table

	  */
