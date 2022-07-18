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

void	display(t_data *data, int dimensions[2])
{
	int x;
	int y;

	y = 0;
	while (y < dimensions[1])
	{
		x = 0;
		while(x < dimensions[0])
		{
			// ft_printf("x is %d, y is %d, z is %d, color is %X in 3D\n", data->array[y][x].x, data->array[y][x].y, data->array[y][x].z, data->array[y][x].color);
			ft_printf("x is %d, y is %d in 2D, color is %d\n", data->array[y][x].x_screen, data->array[y][x].y_screen, data->array[y][x].color);
			ft_printf("---------------------------------------------------------\n");
			x++;
		}
		y++;
	}
	return ;
}

int	render_map(t_data *data)
{
	int j;
	int i;
	int	y;
	int	x;

	j = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			// printf("x position is %d, y position is %d\n", i, j);
			y = 0;
			while(y < data->length)
			{
				x = 0;
				while (x < data->width)
				{
					if(data->array[y][x].x_screen == i && data->array[y][x].y_screen == j)
						img_pix_put(&data->img, i, j, WHITE_PIXEL);//data.array[j][i].color);
					x++;
				}
				y++;
			}
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
	data.width = dimensions[0];
	data.length = dimensions[1];
	// display(&data, dimensions);
	// printf("red macro is %d\n", RED_PIXEL);

	conversion_3D_to_2D(&data);
	// display(&data, dimensions);

// /****printing the points****/
	data.mlx_ptr = mlx_init();
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
	free(data.mlx_ptr);
	free_data(data, dimensions);
	return (0);
}


///1, write a rotation matrix that takes theta and initializes the rotation matrix
///2. write a function that multiplies two matrices
///2. multiply every point of the structure by the rotation matrix which gives you the 2D points
///3. draw the pixel: you need a limiter in your put pix function to make sure the points are in the screen
///4.
