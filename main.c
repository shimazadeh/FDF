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

int	rendering(t_data data)
{
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img,
			&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	draw(&data);
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, NULL);
	mlx_mouse_hook(data.win_ptr, &handle_mouse_release, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 33, 131072, &close_window, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

int	main(int ac, char **ag)
{
	int		fd;
	t_data	data;

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
			return (perror(NULL), -1);
	}
	else
		return (ft_printf("invalid number of arguments\n"), -1);
	if (number_of_lines(fd, &data) < 0)
		return (-1);
	fd = open(ag[1], O_RDONLY);
	create_data_structure(fd, &data);
	rotate(&data);
	rendering(data);
	free_data(data);
	return (0);
}
