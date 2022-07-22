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

void	display(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->length)
	{
		x = 0;
		while(x < data->width)
		{
			ft_printf("(%d,%d,%d,%X) in 3D\n", data->array[y][x].x, data->array[y][x].y, data->array[y][x].z, data->array[y][x].color);
			// ft_printf("x is %d, y is %d in 2D, color is %d\n", data->array[y][x].x_screen, data->array[y][x].y_screen, data->array[y][x].color);
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
	while(y < data->length)
	{
		x = 0;
		while (x < data->width)
		{
			img_pix_put(&data->img, data->array[y][x].x_screen, data->array[y][x].y_screen, data->array[y][x].color);//data.array[j][i].color);
			if (y != data->length - 1)
				evaluate_conditions_execute(&data->array[y][x], &data->array[y + 1][x], data->img);
			if (x != data->width - 1)
				evaluate_conditions_execute(&data->array[y][x], &data->array[y][x + 1], data->img);
			x++;
		}
		y++;
	}
	// drawing_lines(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0 , 0);
	return (0);
}


int	draw_background(t_data *data)
{
	int j;
	int i;

	j = 0;
	if (data->win_ptr == NULL)
		return (1);
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			img_pix_put(&data->img, i, j, encode_rgb(0,0,0));
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

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
			return (ft_printf("error opening the map\n"), -1);
		ft_printf("the value of fd is %d\n", fd);
	}
	else
		return (ft_printf("invalid number of arguments\n"), -1);
	if (number_of_lines(fd, &data) < 0)
		return (-1);

	fd = open(ag[1], O_RDONLY);
/****parsing and converting the dimensions****/
	fdf_parsing(fd, &data);
	// display(&data);
	// printf("the width is %d, the length is %d\n", data.width, data.length);

	// isometric_projection(&data, 0.523599);
	// display(&data);
	data.roll = 2 * 0.174533;
	data.pitch = -0.785398;
	data.yaw = 2 *0.523599;
	// translate_data(&data,-30 * (data.width)/2, -30 * (data.length)/2);
	rotate_data(&data);
	// display(&data);

/****printing the points****/

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
	render_map(&data);

	mlx_loop_hook(data.mlx_ptr, &handle_no_event, NULL);
	mlx_mouse_hook(data.win_ptr,  &handle_mouse_release, &data);
	// mlx_hook(data.win_ptr, ButtonRelease, ButtonReleaseMask, &handle_mouse_release, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 33, 131072, &close_window, &data);

	mlx_loop(data.mlx_ptr);
//	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_data(data);
	return (0);
}
