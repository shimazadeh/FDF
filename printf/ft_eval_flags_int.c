/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_flags_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:05:57 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/04 18:22:38 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_eval_space(t_print *tab, int src)
{
	char	*src2;
	char	*src3;

	src2 = ft_int_add_char(src, ' ');
	if (tab->pnt == 1)
	{
		if (tab->precision == 0 && src == 0)
			src3 = ft_strndup(src2, 1);
		else
			src3 = ft_str_padding(tab->precision + 1, src2, "0", 1);
		free (src2);
	}
	else
		src3 = src2;
	return (src3);
}

char	*ft_eval_sign(t_print *tab, int src)
{
	char	*src2;
	char	*src3;

	src2 = ft_int_add_char(src, '+');
	if (tab->pnt == 1)
	{
		if (tab->precision == 0 && src == 0)
			src3 = ft_strndup(src2, 1);
		else
			src3 = ft_str_padding(tab->precision + 1, src2, "0", 1);
		free (src2);
	}
	else
		src3 = src2;
	return (src3);
}

char	*ft_eval_precision_int(t_print *tab, int src)
{
	char	*src2;
	char	*src3;

	if (src == 0 && tab->pnt == 1 && tab->precision == 0)
	{
		src2 = (char *)malloc(sizeof(char) * 1);
		src2[0] = '\0';
	}
	else
		src2 = ft_itoa(src);
	if (tab->pnt == 1)
	{
		if (src < 0)
			src3 = ft_str_padding(tab->precision + 1, src2, "0", 1);
		else
			src3 = ft_str_padding(tab->precision, src2, "0", 0);
		free(src2);
	}
	else
		src3 = src2;
	return (src3);
}

char	*ft_eval_flags_int(t_print *tab, int src)
{
	char	*src3;

	if (tab->space)
		src3 = ft_eval_space(tab, src);
	if (tab->sign)
		src3 = ft_eval_sign(tab, src);
	if (!tab->sign && !tab->space)
		src3 = ft_eval_precision_int(tab, src);
	return (src3);
}

char	*ft_eval_width_str(t_print *tab, char *src2)
{
	char	*res;

	if (tab->width)
	{
		if (!tab->zero && !tab->dash)
			res = ft_str_padding(tab->width, src2, " ", 0);
		if (tab->zero)
			res = ft_str_padding(tab->width, src2, "0", 0);
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", ft_strlen(src2));
		free(src2);
	}
	else
		res = src2;
	return (res);
}
