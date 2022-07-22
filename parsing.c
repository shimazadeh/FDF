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
//	int	j;

	i = data.length;
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

int	number_of_lines(int fd, t_data *data)
{
	char	*buffer;
	int		dimension[2];

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
		// if (dimension[0] != ft_size_word(buffer, ' '))
			// return (ft_printf("inconsistent line length\n") , -1);
		dimension[1]++;
//		ft_printf("the line is: %s\n", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	data->width = dimension[0];
	data->length = dimension[1];
	close(fd);
	return (0);
}

void	fdf_parsing(int fd, t_data *data)
{
	char	*buffer;
	char	**tab;
	int		y;
	int		x;
	char	**color;

	if (fd < 0)
		return ;
	y = 0;
	buffer = get_next_line(fd);
	data->scale = sqrt((WINDOW_HEIGHT * WINDOW_WIDTH) / (data->width * data->length)) - 1;
	data->array = (t_array **) malloc((sizeof(t_array *)) * (data->length));
	while (ft_strlen(buffer) > 0)//check what the line in files end with, its not \n
	{
		x = 0;
		tab = ft_split(buffer, ' ');
		data->array[y] = (t_array *)malloc(sizeof(t_array) * (data->width));
		while (tab[x] && x < data->width)
		{
			data->array[y][x].x = x * data->scale - (data->scale * data->width / 2); //113 pixel is 5cm
			data->array[y][x].y = y * data->scale - (data->scale * data->length / 2);
			color = ft_split(tab[x], ',');
			data->array[y][x].z = ft_atoi(color[0]) * 2;
			// printf("color is %s\n", color[1]);
			if(!color[1])
			{
				if (data->array[y][x].z == 0)
					data->array[y][x].color = encode_rgb(255, 255, 255); //default is white
				else
					// data->array[y][x].color = encode_rgb(255, 0, 0);
					data->array[y][x].color = encode_rgb(255, 255 / (ft_atoi(color[0])), 0);
			}
			else
				data->array[y][x].color = ft_atoi_base(color[1], "0123456789ABCDEF");
			// printf("the color for z %d, is %d\n",data->array[y][x].z, data->array[y][x].color );
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
	return ;
}

int	encode_rgb(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
