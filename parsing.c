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

int	encode_rgb(u_int8_t red, u_int8_t green, u_int8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	put_to_upper(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return ;
}

int	number_of_lines(int fd, t_data *data)
{
	char	*buffer;
	int		dimension[2];

	dimension[0] = 0;
	dimension[1] = 0;
	if (fd < 0)
		return (perror(NULL), -1);
	buffer = get_next_line(fd);
	if (!buffer)
		return (ft_printf("empty file\n"), -1);
	dimension[0] = ft_size_word(buffer, ' ') - 1;
	while (ft_strlen(buffer) > 0)//check what the line in files end with, its not \n
	{
		dimension[1]++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	data->width = dimension[0];
	data->length = dimension[1];
	close(fd);
	return (0);
}

void	set_map_values(t_data *data, t_array *array, char **tab, int y)
{
	int x;
	char **content;

	x = 0;
	while (tab[x] && x < data->width)
	{
		array[x].x = x * data->scale - (data->scale * data->width / 2);
		array[x].y = y * data->scale - (data->scale * data->length / 2);
		content = ft_split(tab[x], ',');
		array[x].z = ft_atoi(content[0]) * data->scale;
		if(!content[1])
		{
			if (array[x].z == 0)
				array[x].color = encode_rgb(255, 255, 255);
			else
				array[x].color = encode_rgb(255, 255 / (ft_atoi(content[0])), 0);
		}
		else
		{
			put_to_upper(content[1]);
			array[x].color = ft_atoi_base(content[1], "0123456789ABCDEF");
		}
		glob_free(content);
		x++;
	}
	return ;
}

void	create_data_structure(int fd, t_data *data)
{
	char	*buffer;
	char	**tab;
	int		y;

	if (fd < 0)
		return ;
	y = 0;
	data->roll = 0.523599;
	data->pitch = -0.523599;
	data->yaw = 0.523599;
	data->z_scale = 1;
	data->zoom = 1;
	data->scale = sqrt((WINDOW_HEIGHT * WINDOW_WIDTH) /(2 * (data->width * data->length)));
	data->array = (t_array **) malloc((sizeof(t_array *)) * (data->length));
	buffer = get_next_line(fd);
	while (ft_strlen(buffer) > 0)//check what the line in files end with, its not \n
	{
		tab = ft_split(buffer, ' ');
		data->array[y] = (t_array *)malloc(sizeof(t_array) * (data->width));
		set_map_values(data, data->array[y], tab, y);
		glob_free(tab);
		free(buffer);
		buffer = get_next_line(fd);
		y++;
	}
	free(buffer);
	close(fd);
	return ;
}
