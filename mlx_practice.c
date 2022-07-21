#include "fdf.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (keysym == XK_Up)
	{
		data->roll = data->roll + 0.05;
		data->yaw = data->yaw + 0.05;
		draw_background(data);
		rotate_data(data);
		render_map(data);
	}
	if (keysym == XK_Down)
	{
		data->roll = data->roll - 0.05;
		draw_background(data);
		rotate_data(data);
		render_map(data);
	}
	if (keysym == XK_Right)
	{
		data->pitch = data->pitch + 0.05;
		draw_background(data);
		rotate_data(data);
		render_map(data);
	}
	if (keysym == XK_Left)
	{
		data->pitch = data->pitch - 0.05;
		draw_background(data);
		rotate_data(data);
		render_map(data);
	}
	//two keys for yaw rotation
	// printf("keypress: %d\n", keysym);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	if (button == 4)
	{
		draw_background(data);
		zoom(data, 1.5);
		render_map(data);
		printf("zoom in\n");
	}
	if (button == 5)
	{
		draw_background(data);
		zoom(data, 0.5);
		render_map(data);
		printf("zoom out\n");
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
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
	return ;
}

int	handle_no_event(void *data)
{
	(void)data;
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}
