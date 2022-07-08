/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:50:00 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/02 19:00:14 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*ft_eval_precision_ex(t_print *tab, char *src)
{
	char	*src2;

	if (tab->precision == 0 && src[0] == '0')
	{
		src2 = (char *)malloc(sizeof(char) * 1);
		src2[0] = '\0';
	}
	else
	{
		src2 = ft_str_padding(tab->precision, src, "0", 0);
	}
	free(src);
	return (src2);
}

char	*ft_eval_flags_ex(t_print *tab, char *src, char *x)
{
	char	*src2;
	char	*src3;

	if (src[0] == '0')
		tab->hashtag = 0;
	if (tab->pnt == 1)
	{
		src2 = ft_eval_precision_ex(tab, src);
	}
	else
		src2 = src;
	if (tab->hashtag)
	{
		src3 = ft_str_multi_padding_left(src2, x);
		free(src2);
	}
	else
		src3 = src2;
	return (src3);
}

char	*ft_eval_width_ex(t_print *tab, char *src2)
{
	char	*res;

	if (tab->width)
	{
		if (!tab->dash && !tab->zero)
			res = ft_str_padding(tab->width, src2, " ", 0);
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", ft_strlen(src2));
		if (tab->zero)
		{
			if (tab->hashtag && tab->pnt == 0)
				res = ft_str_padding(tab->width, src2, "0", 2);
			if (!tab->hashtag && tab->pnt == 0)
				res = ft_str_padding(tab->width, src2, "0", 0);
			if (tab->pnt == 1)
				res = ft_str_padding(tab->width, src2, " ", 0);
		}
		free(src2);
	}
	if (!tab->width)
		res = src2;
	return (res);
}

char	*ft_eval_precision_dec(t_print *tab, unsigned int d)
{
	char	*src3;
	char	*src2;

	if (tab->pnt == 1)
	{
		src3 = ft_itoa(d);
		if (tab->precision == 0 && d == 0)
		{
			src2 = (char *)malloc(sizeof(char) * 1);
			src2[0] = '\0';
		}
		else
			src2 = ft_str_padding(tab->precision, src3, "0", 0);
		free(src3);
	}
	else
		src2 = ft_itoa(d);
	return (src2);
}

int	ft_eval_char_null(t_print *tab, char src)
{
	char	*src2;
	char	*res;

	src2 = ft_strndup(&src, 0);
	if (tab->width)
	{
		if (tab->dash)
			res = ft_char_padding(tab, src2, " ");
		if (tab->zero)
			res = ft_str_padding(tab->width, src2, "0", 0);
		if (!tab->zero && !tab->dash)
			res = ft_str_padding(tab->width - 1, src2, " ", 0);
		free(src2);
		return (ft_pf_putstr_char_null(tab, res));
	}
	else
		res = src2;
	return (ft_pf_putchar_addr(res));
}
