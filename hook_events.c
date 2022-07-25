#include "fdf.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	else if (keysym == XK_Up || keysym == XK_Down || keysym == XK_a || keysym == XK_d || keysym == XK_w || keysym == XK_x || keysym == XK_e || keysym == XK_z)
	{
		if (keysym == XK_Up)
			data->z_scale = 2;
		else if (keysym == XK_Down)
			data->z_scale = 0.80;
		else if (keysym == XK_a)
			data->roll = data->roll + 0.05;
		else if (keysym == XK_d)
			data->roll = data->roll - 0.05;
		else if (keysym == XK_w)
			data->pitch = data->pitch + 0.05;
		else if (keysym == XK_x)
			data->pitch = data->pitch - 0.05;
		else if (keysym == XK_e)
			data->yaw = data->yaw + 0.05;
		else if (keysym == XK_z)
			data->yaw = data->yaw - 0.05;
		re_draw(data, keysym);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;

	if (button == 4)
	{
		data->zoom = 1.1;
		re_draw(data, button);
	}
	if (button == 5)
	{
		data->zoom = 0.9;
		re_draw(data, button);
	}
	return (0);
}

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

void	re_draw(t_data *data, int keysym)
{
	if (keysym == XK_Up || keysym == XK_Down)
		scale_z(data, data->z_scale);
	else if (keysym == 4 || keysym == 5)
		zoom(data, data->zoom);
	draw_background(data);
	rotate(data);
	draw(data);
	return ;
}