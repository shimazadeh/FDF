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

t_matrix	initialize_rotation_x_axis(double angle)
{
	t_matrix matrix;

	matrix.rows = 3;
	matrix.columns = 3;
	matrix.data = (double **)malloc(sizeof(double *) * 3);

	matrix.data[0] = (double *)malloc(sizeof(double) * 3);
	matrix.data[0][0] = 1;
	matrix.data[0][1] = 0;
	matrix.data[0][2] = 0;

	matrix.data[1] = (double *)malloc(sizeof(double) * 3);
	matrix.data[1][0] = 0;
	matrix.data[1][1] = cos(angle);
	matrix.data[1][2] = -sin(angle);

	matrix.data[2] = (double *)malloc(sizeof(double) * 3);
	matrix.data[2][0] = 0;
	matrix.data[2][1] = sin(angle);
	matrix.data[2][2] = cos(angle);
	return (matrix);
}

t_matrix	initialize_rotation_y_axis(double angle)
{
	t_matrix matrix;

	matrix.rows = 3;
	matrix.columns = 3;
	matrix.data = (double **)malloc(sizeof(double *) * 3);

	matrix.data[0] = (double *)malloc(sizeof(double) * 3);
	matrix.data[0][0] = cos(angle);
	matrix.data[0][1] = 0;
	matrix.data[0][2] = sin(angle);

	matrix.data[1] = (double *)malloc(sizeof(double) * 3);
	matrix.data[1][0] = 0;
	matrix.data[1][1] = 1;
	matrix.data[1][2] = 0;

	matrix.data[2] = (double *)malloc(sizeof(double) * 3);
	matrix.data[2][0] = -sin(angle);
	matrix.data[2][1] = 0;
	matrix.data[2][2] = cos(angle);
	return (matrix);
}

t_matrix	initialize_rotation_z_axis(double angle)
{
	t_matrix matrix;

	matrix.rows = 3;
	matrix.columns = 3;
	matrix.data = (double **)malloc(sizeof(double *) * 3);

	matrix.data[0] = (double *)malloc(sizeof(double) * 3);
	matrix.data[0][0] = cos(angle);
	matrix.data[0][1] = -sin(angle);
	matrix.data[0][2] = 0;

	matrix.data[1] = (double *)malloc(sizeof(double) * 3);
	matrix.data[1][0] = sin(angle);
	matrix.data[1][1] = cos(angle);
	matrix.data[1][2] = 0;

	matrix.data[2] = (double *)malloc(sizeof(double) * 3);
	matrix.data[2][0] = 0;
	matrix.data[2][1] = 0;
	matrix.data[2][2] = 1;
	return (matrix);
}

t_matrix	multiply_two_matrix(t_matrix A, t_matrix B)
{
	t_matrix 	res;
	int			i;
	int			j;

	i = 0;
	// if (A.columns != B.rows)
	// 	return (NULL);
	res.rows = A.rows;
	res.columns = B.columns;
	res.data = (double **) malloc(sizeof(double *) * A.rows);
	while (i < A.rows)
	{
		res.data[i] = (double *)malloc(sizeof(double *) * B.columns);
		j = 0;
		while(j < B.columns)
		{
			res.data[i][j] = A.data[i][0]*B.data[0][j] + A.data[i][1]*B.data[1][j] + A.data[i][2]*B.data[2][j];
			j++;
		}
		i++;
	}
	return (res);
}

void	update_2D_coordinates(t_array *array, t_matrix rotation)
{
	t_matrix	temp;
	t_matrix 	res;
	int			i;
	int			j;

	temp.rows = 3;
	temp.columns = 1;
	temp.data = (double **)malloc(sizeof(double *) * 3);
	temp.data[0] = (double *)malloc(sizeof(double) * 1);
	temp.data[1] = (double *)malloc(sizeof(double) * 1);
	temp.data[2] = (double *)malloc(sizeof(double) * 1);

	temp.data[0][0] = (double) array->x;
	temp.data[1][0] = (double) array->y;
	temp.data[2][0] = (double) array->z;

	// printf("%d, %d, %d\n", array.x, array.y, array.z);
	// printf("%f, %f, %f\n", temp.data[0][0], temp.data[1][0], temp.data[2][0]);
	res.data = (double **) malloc(sizeof(double *) * rotation.rows);
	i = 0;
	// printf("-----the raw value-----\n");
	while (i < rotation.rows)
	{
		res.data[i] = (double *)malloc(sizeof(double *) * temp.columns);
		j = 0;
		while(j < temp.columns)
		{
			res.data[i][j] = rotation.data[i][0]*temp.data[0][j] + rotation.data[i][1]*temp.data[1][j] + rotation.data[i][2]*temp.data[2][j];
			// printf("%f", res.data[i][j]);
			j++;
			// printf("%f ", temp.data[0][j]);
			// printf("%f ", temp.data[1][j]);
			// printf("%f", temp.data[2][j]);
		}
		// printf("\n");
		i++;
	}
	// printf("----final values------\n");
	array->x_screen = (int) res.data[0][0] + WINDOW_WIDTH / 2;
	array->y_screen = (int) res.data[1][0] + WINDOW_HEIGHT / 5;

	// array->x_screen = ((int)(res.data[0][0] / (int)res.data[2][0]));
	// array->y_screen = ((int)(res.data[0][0] / (int)res.data[2][0]));

	// array->x_screen = (int) ((res.data[0][0] - res.data[2][0]) * cos(1.0472)) + 100;
	// array->y_screen = (int) ((res.data[0][0] + res.data[2][0]) * sin(1.0472) - res.data[2][0]) + 100;
	// array.z_screen = res.data[2][0];
	// printf("%d\n%d\n", array->x_screen, array->y_screen);
	//free(temp)
	//free(res)
	return ;
}

void	conversion_3D_to_2D(t_data *data)
{
	int 		i;
	int 		j;
	t_matrix	x;
	t_matrix	y;
	t_matrix	z;
	t_matrix	rotation;


	x = initialize_rotation_x_axis(2 * 0.174533);
	y = initialize_rotation_y_axis(-0.785398);
	z = initialize_rotation_z_axis(2 * 0.523599);
	rotation = multiply_two_matrix(multiply_two_matrix(z, y), x);
	display_matrix(rotation);

	j = 0;
	while(j < data->length)
	{
		i = 0;
		while(i < data->width)
		{
			update_2D_coordinates(&data->array[j][i], rotation);
			i++;
		}
		j++;
	}
	return ;
}

void	display_matrix(t_matrix A)
{
	int i;
	int j;

	i = 0;
	while(i < 3)
	{
		j = 0;
		while(j < 3)
		{
			printf("%f ", A.data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	return ;
}
