/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:42:00 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/20 15:42:01 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_2D_coordinates(t_array *array, double angle, t_data *data)
{
	array->x_screen = (int) ((array->x - array->y) * cos(angle)) + (WINDOW_WIDTH/ 2);
	array->y_screen = (int) ((array->x + array->y) * sin(angle) - array->z) + ((WINDOW_HEIGHT)/ 2);
	return ;
}

void	isometric_projection(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while(j < data->length)
	{
		i = 0;
		while(i < data->width)
		{
			update_2D_coordinates(&data->array[j][i], 0.523599, data);
			i++;
		}
		j++;
	}
	return ;
}
