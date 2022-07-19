/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_method.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:38:21 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/19 20:38:25 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_array *start, t_array *end,t_img img)
{
	double step_x;
	double step_y;
	double x_diff;
	double y_diff;
	double i;
	double j;
	double max;


	// printf("the start (%d, %d), end (%d, %d)\n", start->x_screen, start->y_screen, end->x_screen, end->y_screen);
	x_diff = end->x_screen - start->x_screen;
	y_diff = end->y_screen - start->y_screen;
	if (y_diff > x_diff)
		max = y_diff;
	else
		max = x_diff;
	step_x = x_diff / max;
	step_y = y_diff / max;

	i = start->x_screen;
	j = start->y_screen;
	while(i < end->x_screen - 1)
	{
		i =  i + step_x;
		j = j + step_y;
		img_pix_put(&img, i, j, RED_PIXEL);
		// printf("the next point to print (%f, %f)\n", i, j);
	}
	return ;
}


void	evaluate_conditions_execute(t_array *start, t_array *end, t_img	img)
{
	if (end->x_screen < start->x_screen && end->y_screen < start->y_screen)
		bresenham(end, start, img);
	else
		bresenham(start, end, img);
	return ;
}

void	drawing_lines(t_data *data)
{
	int x;
	int y;

	y = 0;
	// printf("here:\n");
	while (y < data->length)
	{
		x = 0;
		// printf("width is %d\n", data->width);
		while (x < data->width)
		{
			// printf("the x is %d\n", x);
			if (y != data->length - 1)
			{
				// printf("the start point: %d, %d\n", data->array[y][x].x, data->array[y][x].y);
				// printf("the end point: %d, %d\n", data->array[y + 1][x].x, data->array[y + 1][x].y);
				evaluate_conditions_execute(&data->array[y][x], &data->array[y + 1][x], data->img);
			}
			if (x != data->width - 1)
			{
				// printf("the start point: %d, %d\n", data->array[y][x].x, data->array[y][x].y);
				// printf("the end point: %d, %d\n", data->array[y][x + 1].x, data->array[y][x + 1].y);
				evaluate_conditions_execute(&data->array[y][x], &data->array[y][x + 1], data->img);
			}
			// printf("--------------\n");
			x++;
		}
		y++;
	}
	return ;
}
