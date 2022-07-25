/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:03:17 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/25 13:03:19 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	draw(t_data *data)
{
	int	y;
	int	x;

	y = 0;
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0 , 0);
	return (0);
}

void	draw_line(t_array *start, t_array *end,t_img img)
{
	double i;
	double j;
	double color;
	double max;

	if ((end->y_screen - start->y_screen) > (end->x_screen - start->x_screen))
		max = end->y_screen - start->y_screen;
	else
		max = end->x_screen - start->x_screen;

	i = start->x_screen;
	j = start->y_screen;
	color = start->color;
	while(i < end->x_screen - 1)
	{
		i =  i + ((end->x_screen - start->x_screen) / max);
		j = j + ((end->y_screen - start->y_screen) / max);
		color = color + ((end->color - start->color)/ max);
		img_pix_put(&img, i, j, color);
	}
	return ;
}

void	evaluate_conditions_execute(t_array *start, t_array *end, t_img	img)
{
	if (end->x_screen < start->x_screen)// && end->y_screen < start->y_screen)
		draw_line(end, start, img);
	else
		draw_line(start, end, img);
	return ;
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
