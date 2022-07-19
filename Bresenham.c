/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:36:54 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/19 13:36:55 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_array *start, t_array *end, int flag, t_img	img)
{
	int	p;
	int	delta_y;
	int delta_x;
	int	k;
	int pixel_x;
	int pixel_y;

	delta_x = end->x_screen - start->x_screen;
	delta_y = end->y_screen - start->y_screen;
	p = 2 * delta_y - delta_x;
	k = 1;
	pixel_x = start->x_screen;
	pixel_y = start->y_screen;
	// printf("delta_x is %d, delta_y is %d\n", delta_x, delta_y);
	while(k < delta_x)
	{
		if (p < 0)
		{
			if (flag == 2)//y sign is the opposite
				img_pix_put(&img, ++pixel_x, -1 * (pixel_y), RED_PIXEL);
				// printf("the x,y of the new point:(%d,%d)\n", ++pixel_x, -1 * (pixel_y));
			if (flag == 1)//x and y are swapped
				img_pix_put(&img, pixel_y, ++pixel_x, WHITE_PIXEL);
				// printf("the new point to plot: (%d,%d)\n", pixel_y, ++pixel_x);
			if (flag == 0)//default
				img_pix_put(&img, ++pixel_x, pixel_y, GREEN_PIXEL);
				// printf("the new point to plot: (%d,%d)\n", ++pixel_x, pixel_y);
			p = p + 2 * delta_y;
		}
		else
		{
			if (flag == 2)
				img_pix_put(&img, ++pixel_x, -1 * (pixel_y), RED_PIXEL);
				// printf("the new point to plot: (%d, %d)\n", ++pixel_x, -1 * (++pixel_y));
			if (flag == 1)
				img_pix_put(&img, pixel_y, ++pixel_x, WHITE_PIXEL);
				// printf("the new point to plot: (%d, %d)\n", ++pixel_y, ++pixel_x);
			if (flag == 0)
				img_pix_put(&img, ++pixel_x, pixel_y, GREEN_PIXEL);
				// printf("the new point to plot: (%d, %d)\n", ++pixel_x, ++pixel_y);
			p = p + 2 *(delta_y) - 2 * (delta_x);
		}
		k++;
	}
	return ;
}

void	evaluate_conditions_execute(t_array *start, t_array *end, t_img	img)
{
	t_array temp_start;
	t_array temp_end;
	int		slope;
	int		i;

	i = start->x_screen;
	slope = (end->y_screen - start->y_screen) / (end->x_screen - start->x_screen);
	printf("slope is %d\n", slope);
	if (end->x_screen < start->x_screen && end->y_screen < start->y_screen)//flag 0
		bresenham(end, start, 0, img);
	else if (slope < 0)//flag 2
	{
		temp_start.x_screen = start->x_screen;
		temp_start.y_screen = -(start->y_screen);
		temp_end.x_screen = end->x_screen;
		temp_end.y_screen = -(end->y_screen);
		bresenham(&temp_start, &temp_end, 2, img);
	}
	else if (slope > 1)//flag 1
	{
		temp_start.x_screen = start->y_screen;
		temp_start.y_screen = start->x_screen;
		temp_end.x_screen = end->y_screen;
		temp_end.y_screen = end->x_screen;
		bresenham(&temp_start, &temp_end, 1, img);
	}
	else if (slope == 0)
	{
		printf("drawing");
		while(i < end->x_screen)
			img_pix_put(&img, i++, start->y_screen, WHITE_PIXEL);
		printf("\n");
	}
	else
		bresenham(start, end, 0, img);//flag 0
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
		while (x < data->width)
		{
			// printf("the starting point: %d, %d\n", data->array[y][x].x_screen, data->array[y][x].y_screen);
			if (y != data->length - 1)
			{
				// printf("the end point: %d, %d\n", data->array[y + 1][x].x_screen, data->array[y + 1][x].y_screen);
				evaluate_conditions_execute(&data->array[y][x], &data->array[y + 1][x], data->img);
			}
			if (x != data->width - 1)
			{
				// printf("the end point: %d, %d\n", data->array[y][x + 1].x_screen, data->array[y][x + 1].y_screen);
				evaluate_conditions_execute(&data->array[y][x], &data->array[y][x + 1], data->img);
			}
			// printf("--------------\n");
			x++;
		}
		y++;
	}
	return ;
}
/*
int	main(int ac, char **ag)
{
	(void)ac;
	(void)ag;
	t_array a;
	t_array b;

	a.x_screen = 5;
	a.y_screen = 5;

	b.x_screen = 2;
	b.y_screen = 2;
	bresenham(&a, &b);
	return (0);
}
*/
