/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:10:05 by shabibol          #+#    #+#             */
/*   Updated: 2022/07/08 19:10:07 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_data(t_data data)
{
	int	i;

	i = 0;
	while (data.array && data.array[i])
		i++;
	while (i > 0)
	{
		i--;
		free(data.array[i]);
	}
	free(data.array);
	return ;
}

char	**glob_free(char **dst)
{
	int	i;

	i = 0;
	while (dst && dst[i])
		i++;
	while (i > 0)
	{
		i--;
		free((void *)dst[i]);
	}
	free (dst);
	return (NULL);
}

int	number_of_lines(int fd, int dimension[2])
{
	char	*buffer;

	dimension[0] = 0;
	dimension[1] = 0;
	if (fd < 0)
		return (ft_printf("error reading the file\n"), -1);
	buffer = get_next_line(fd);
	if (!buffer)
		return (ft_printf("empty file\n"), -1);
	dimension[0] = ft_size_word(buffer, ' ') - 1;
	while (ft_strlen(buffer) > 0)//check what the line in files end with, its not \n
	{
		if (dimension[0] != ft_size_word(buffer, ' ') - 1)
			return (ft_printf("inconsistent line length\n") , -1);
		dimension[1]++;
		ft_printf("the line is: %s\n", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	close(fd);
	return (0);
}

t_data	fdf_parsing(int fd, int dimensions[2])
{
	char	*buffer;
	char	**tab;
	t_data	data;
	int		y;
	int		x;
	char	**color;

	if (fd < 0)
		return (data);
	y = 0;
	buffer = get_next_line(fd);
	data.array = (t_array **) malloc((sizeof(t_array *)) * (dimensions[1]));
	while (ft_strlen(buffer) > 0)//check what the line in files end with, its not \n
	{
		x = 0;
		tab = ft_split(buffer, ' ');
		data.array[y] = (t_array *)malloc(sizeof(t_array) * (dimensions[0]));
		while (tab[x] && x < dimensions[0])
		{
			data.array[y][x].x = x;
			data.array[y][x].y = y;
			if (ft_strchr(tab[x], ','))
			{
				color = ft_split(tab[x], ',');
				data.array[y][x].z = ft_atoi(color[0]);
				printf("color is %s\n", color[1]);
				data.array[y][x].color =ft_strdup(color[1]);
//				glob_free(color);
			}
			else
			{
				data.array[y][x].z = ft_atoi(tab[x]);
				data.array[y][x].color = 0; //default
			}
			ft_printf("x is %d, y is %d, z is %d, color is %s\n", data.array[y][x].x, data.array[y][x].y, data.array[y][x].z, data.array[y][x].color);
			x++;
		}
		ft_printf("-------next line--------\n");
		glob_free(tab);
		free(buffer);
		buffer = get_next_line(fd);
		y++;
	}
	free(buffer);
	close(fd);
	return (data);
}

int	main(int ac, char **ag)
{
	int 	fd;
	t_data	data;
	int		dimensions[2];

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
			return (ft_printf("error opening the map\n"), -1);
		ft_printf("the value of fd is %d\n", fd);
	}
	else
		return (ft_printf("invalid number of arguments\n"), -1);
	if (number_of_lines(fd, dimensions) < 0)
		return (-1);
	ft_printf("width is %d, length is %d\n", dimensions[0], dimensions[1]);
	fd = open(ag[1], O_RDONLY);
	data = fdf_parsing(fd, dimensions);
	free_data(data);
	return (0);
}


/*step1: read the file line by line using get_next_line
			 parse each line (if its not integer print a message and exit)
			 store the values as an array which is part of the structure? (x, y, z, color)
			 checks:
			 	some numbers include a specific color separated by comma (,)
				the length of all rows must be equal to each other
			store the dimension of the map

	  step2:
			use the structure created previously to draw each point
			connect the points using the bresenham algorithm

array = two dimensional table

	  */
