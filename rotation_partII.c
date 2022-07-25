/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_partII.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:58:20 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/25 12:58:22 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_point(t_array *array, t_matrix rotation)
{
	double		temp[3][1];
	double		res[3][1];
	int			i;
	int			j;

	temp[0][0] = (double) array->x;
	temp[1][0] = (double) array->y;
	temp[2][0] = (double) array->z;
	i = 0;
	while (i < rotation.rows)
	{
		j = 0;
		while (j < 1)
		{
			res[i][j] = rotation.data[i][0] * temp[0][j]
				+ rotation.data[i][1] * temp[1][j]
				+ rotation.data[i][2] * temp[2][j];
			j++;
		}
		i++;
	}
	array->x_screen = (int) res[0][0] + WIN_WIDTH / 2;
	array->y_screen = (int) res[1][0] + WIN_HEIGHT / 2;
	return ;
}

void	rotate(t_data *data)
{
	int			i;
	int			j;
	t_matrix	rotation;

	rotation = initialize_rotation(data->roll, data->pitch, data->yaw);
	j = 0;
	while (j < data->length)
	{
		i = 0;
		while (i < data->width)
		{
			rotate_point(&data->array[j][i], rotation);
			i++;
		}
		j++;
	}
	free_matrix(rotation);
	return ;
}

void	zoom(t_data *data, double zoom)
{
	int			i;
	int			j;

	j = 0;
	while (j < data->length)
	{
		i = 0;
		while (i < data->width)
		{
			data->array[j][i].x = data->array[j][i].x * zoom;
			data->array[j][i].y = data->array[j][i].y * zoom;
			data->array[j][i].z = data->array[j][i].z * zoom;
			i++;
		}
		j++;
	}
	return ;
}

void	scale_z(t_data *data, double scale)
{
	int			i;
	int			j;

	j = 0;
	while (j < data->length)
	{
		i = 0;
		while (i < data->width)
		{
			data->array[j][i].z = data->array[j][i].z * scale;
			i++;
		}
		j++;
	}
	return ;
}

void	translate_data(t_data *data, int translate, int flag)
{
	int			i;
	int			j;

	j = 0;
	while (j < data->length)
	{
		i = 0;
		while (i < data->width)
		{
			if (flag == 0)
			{
				data->array[j][i].x = data->array[j][i].x + translate;
				data->array[j][i].y = data->array[j][i].y + translate;
			}
			if (flag == 1)
			{
				data->array[j][i].y = data->array[j][i].y + translate;
				data->array[j][i].z = data->array[j][i].z + translate;
			}
			i++;
		}
		j++;
	}
	return ;
}
