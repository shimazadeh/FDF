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


///1, write a rotation matrix that takes theta and initializes the rotation matrix

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

t_matrix	multiple_two_matrix(t_matrix A, t_matrix B)
{
	t_matrix 	res;
	int			i;
	int			j;

	i = 0;
	// if (A.rows != B.columns)
	// 	return (NULL);
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

int	main(int ac, char **argc)
{
	t_matrix	x;
	t_matrix	y;
	t_matrix	z;
	t_matrix	res;
	t_matrix	temp;
	int			i;
	int			j;

	x = initialize_rotation_x_axis(1.5708);
	y = initialize_rotation_y_axis(1.5708);
	z = initialize_rotation_z_axis(1.5708);

	temp = multiple_two_matrix(y,z);
	res = multiple_two_matrix(temp, x);

	display_matrix(x);
	display_matrix(y);
	display_matrix(z);
	display_matrix(temp);
	display_matrix(res);
	return (0);
}

///2. write a function that multiplies two matrices
///3. multiply every point of the structure by the rotation matrix which gives you the 2D points
