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

int	main(int ac, char **ag)
{
	int fd1;

	if (ac == 2)
		fd1 = open(ag[1], O_RDONLY);
	else
		ft_printf("invalid number of arguments\n");
	/*step1: read the file line by line using get_next_line
			 parse each line (use split , if its not integer print a message and exit)
			 store the values as a structure/chain list? (x, y, z, color)
			 some numbers include a specific color separated by comma (,)

	  step2:

	  */
}
