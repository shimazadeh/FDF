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
	t_matrix	matrix;

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
	t_matrix	matrix;

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
	t_matrix	matrix;

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
	t_matrix	res;
	int			i;
	int			j;

	i = 0;
	res.rows = A.rows;
	res.columns = B.columns;
	res.data = (double **) malloc(sizeof(double *) * A.rows);
	while (i < A.rows)
	{
		res.data[i] = (double *)malloc(sizeof(double *) * B.columns);
		j = 0;
		while (j < B.columns)
		{
			res.data[i][j] = A.data[i][0] * B.data[0][j]
				+ A.data[i][1] * B.data[1][j]
				+ A.data[i][2] * B.data[2][j];
			j++;
		}
		i++;
	}
	return (res);
}

t_matrix	initialize_rotation(double roll, double pitch, double yaw)
{
	t_matrix	x;
	t_matrix	y;
	t_matrix	z;
	t_matrix	temp;
	t_matrix	rotation;

	x = initialize_rotation_x_axis(roll);
	y = initialize_rotation_y_axis(pitch);
	z = initialize_rotation_z_axis(yaw);
	temp = multiply_two_matrix(z, y);
	rotation = multiply_two_matrix(temp, x);
	free_matrix(x);
	free_matrix(y);
	free_matrix(z);
	free_matrix(temp);
	return (rotation);
}
