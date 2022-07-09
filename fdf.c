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

int	number_of_lines(int fd)
{
	int 	width;
	char	*buffer;
	int		length;

	if (fd < 0)
		return (-1);
	buffer = get_next_line(fd);
	if (buffer)
		width = 1;
	else
		width = 0;
	tab = ft_split(buffer, ' ');
	length = ft_strlen(*tab);
	while (buffer)
	{
		tab = ft_split(buffer, ' ');
		lines++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (lines);

}
t_data	fdf_parsing(int fd)
{
	char	*buffer;
	char	*tab;
	int		y;
	int		x;

	if (fd < 0)
		return (-1);
	y = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		tab = ft_split(buffer, ' ');
		while (*tab)
			data.array =
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (lines);
}

int	main(int ac, char **ag)
{
	int 	fd;
	char	*buffer;
	t_data	data;

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
			return (ft_printf("error opening the map\n"), -1);
		ft_printf("the value of fd is %d\n", fd);
	}
	else
		return (ft_printf("invalid number of arguments\n"), -1);
	data = fdf_parsing(fd);
	return (0);
}


/*step1: read the file line by line using get_next_line
			 parse each line (use split , if its not integer print a message and exit)
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
