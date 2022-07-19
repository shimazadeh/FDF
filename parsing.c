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

void	free_data(t_data data, int dimensions[2])
{
	int	i;
//	int	j;

	i = dimensions[1];
	while (i > 0)
	{
		i--;
	/*	j = dimensions[0];
		while (j > 0)
		{
			j--;
			free(data.array[i][j].color);
		}*/
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
//		ft_printf("the line is: %s\n", buffer);
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
			data.array[y][x].x = x * 20; //113 pixel is 5cm
			data.array[y][x].y = y * 20;
			color = ft_split(tab[x], ',');
			data.array[y][x].z = ft_atoi(color[0]) * 20;
			// if(!color[1])
				data.array[y][x].color = WHITE_PIXEL; //default is white
			// else
				// data.array[y][x].color = ft_atoi(color[1]);
			glob_free(color);
			x++;
		}
		glob_free(tab);
		free(buffer);
		buffer = get_next_line(fd);
		y++;
	}
	free(buffer);
	close(fd);
	return (data);
}

