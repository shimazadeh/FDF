/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:53:34 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/15 17:53:35 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	initialize_translation(double tx, double ty)
{
	t_matrix matrix;

	matrix.rows = 3;
	matrix.columns = 3;
	matrix.data = (double **)malloc(sizeof(double *) * 3);

	matrix.data[0] = (double *)malloc(sizeof(double) * 3);
	matrix.data[0][0] = 1;
	matrix.data[0][1] = 0;
	matrix.data[0][2] = 0;
	// matrix.data[0][3] = 0;

	matrix.data[1] = (double *)malloc(sizeof(double) * 3);
	matrix.data[1][0] = 0;
	matrix.data[1][1] = 1;
	matrix.data[1][2] = 0;
	// matrix.data[1][3] = 0;

	matrix.data[2] = (double *)malloc(sizeof(double) * 3);
	matrix.data[2][0] = 0;
	matrix.data[2][1] = 0;
	matrix.data[2][2] = 1;
	// matrix.data[2][3] = 0;


	// matrix.data[3] = (double *)malloc(sizeof(double) * 3);
	// matrix.data[3][0] = tx;
	// matrix.data[3][1] = ty;
	// matrix.data[3][2] = 1;
	// // matrix.data[3][3] = 1;
	return (matrix);
}


void	translate(t_array *array, t_matrix translation)
{
	t_matrix	temp;
	t_matrix 	res;
	int			i;
	int			j;

	temp.rows = 1;
	temp.columns = 3;
	temp.data = (double **)malloc(sizeof(double *) * 1);
	temp.data[0] = (double *)malloc(sizeof(double) * 3);

	temp.data[0][0] = (double) array->x_screen;
	temp.data[0][1] = (double) array->y_screen;
	// temp.data[0][2] = (double) array->z;
	temp.data[0][2] = 1;

	res.data = (double **) malloc(sizeof(double *) * temp.rows);
	i = 0;
	while (i < temp.rows)
	{
		res.data[i] = (double *)malloc(sizeof(double *) * translation.columns);
		j = 0;
		while(j < translation.columns)
		{
			res.data[i][j] = temp.data[i][0]*translation.data[0][j] + temp.data[i][1]*translation.data[1][j] + temp.data[i][2]*translation.data[2][j];
			j++;
		}
		i++;
	}
	array->x_screen = (int) res.data[0][0];
	array->y_screen = (int) res.data[0][1];
	// array->z = (int) res.data[0][2];
	//free(temp)
	//free(res)
	return ;
}

void	translate_data(t_data *data, int tx, int ty)
{
	int 		i;
	int 		j;
	t_matrix	translation;

	translation = initialize_translation(tx, ty);

	j = 0;
	while(j < data->length)
	{
		i = 0;
		while(i < data->width)
		{
			data->array[j][i].x = data->array[j][i].x + tx;
			data->array[j][i].y = data->array[j][i].y + ty;
			data->array[j][i].z = data->array[j][i].z;
			// translate(&data->array[j][i], translation);
			i++;
		}
		j++;
	}
	return ;
}
