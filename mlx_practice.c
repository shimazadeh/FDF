#include "fdf.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (keysym == XK_Up)
	{
		printf("rotate around x axis +angle\n");
		data->roll = data->roll + 0.0872665;
		data->pitch = data->pitch + 0.0872665;
		data->yaw = data->yaw + 0.0872665;
		render_map(data);
	}
	// 	// printf("rotate around x axis +angle\n");
	// if (keysym == XK_Down)
	// 	printf("rotate around x axis -angle\n");
	// if (keysym == XK_Left)
	// 	printf("rotate around y axis +angle\n");
	// if (keysym == XK_Right)
	// 	printf("rotate around y axis -angle\n");

	// printf("keypress: %d\n", keysym);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 1 && x < 0 && y < 0)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("mouse release: x is %d, y is %d\n", x, y);
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
}
/*
int render_rect(t_img *img, t_rect rect)
{
	int j;
	int i;

	j = rect.y;
	while (j < rect.y + rect.height)
	{
		i = rect.x;
		while(i < rect.x + rect.width)
		{
			if (i == rect.x || i == rect.x + rect.width - 1)
				img_pix_put(img, i, j, rect.color);
			i++;
		}
		j++;
	}
	return (0);
}

int render_background(t_img *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
	return (0);
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
//	render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
//	render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}*/
/*
int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	//TODO : create main img
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data); //call function to do : #1 calculte stuff #2 rendering stuff according to calculated datas
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

//	mlx_destroy_window(mlx_ptr, mlx_win);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}*/


/*
	//TODO : create main img
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, cub->img.img_ptr, 0, 0);
	mlx_hook(cub->win, 33, 1L << 17, &ft_exit, cub); //cross red event to close window
	mlx_hook(cub->win, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, &key_release, cub);
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data); //call function to do : #1 calculte stuff #2 rendering stuff according to calculated datas
	mlx_key_hook(data.win_ptr, &handle_input, &data);*/
