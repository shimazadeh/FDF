/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_subs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:21:43 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/02 19:02:07 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(t_print *tab)
{
	char	src;
	char	*src2;
	char	*res;

	src = va_arg(tab->arg, int);
	if (src == 0)
		return (ft_eval_char_null(tab, src));
	else
		src2 = ft_strndup(&src, 1);
	if (tab->width)
	{
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", 1);
		if (tab->zero)
			res = ft_str_padding(tab->width, src2, "0", 0);
		if (!tab->zero && !tab->dash)
			res = ft_str_padding(tab->width, src2, " ", 0);
		free(src2);
		return (ft_pf_putstr_char(res));
	}
	else
		res = src2;
	return (ft_pf_putchar_addr(res));
}

int	ft_printstr(t_print *tab)
{
	char	*src;
	char	*res;
	char	*src2;

	src = va_arg(tab->arg, char *);
	if (src == NULL)
		res = ft_assign_null(tab);
	else
	{
		src2 = ft_str_cut(tab, src);
		res = ft_eval_width_str(tab, src2);
	}
	return (ft_pf_putstr(res));
}

int	ft_printinteger(t_print *tab)
{
	char	*res;
	int		src;
	char	*src2;

	src = va_arg(tab->arg, int);
	src2 = ft_eval_flags_int(tab, src);
	if (tab->width)
	{
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", ft_strlen(src2));
		if (tab->zero && tab->pnt == 0 && ft_strchr_boolean(*src2, "+-") == 0)
			res = ft_str_padding(tab->width, src2, "0", 0);
		if (tab->zero && tab->pnt == 0 && ft_strchr_boolean(*src2, "+- ") == 1)
			res = ft_str_padding(tab->width, src2, "0", 1);
		if (tab->zero && tab->pnt == 1)
			res = ft_str_padding(tab->width, src2, " ", 0);
		if (!tab->dash && !tab->zero)
			res = ft_str_padding(tab->width, src2, " ", 0);
		free(src2);
	}
	if (!tab->width)
		res = src2;
	return (ft_pf_putstr(res));
}

int	ft_printdecimal(t_print *tab)
{
	char			*res;
	char			*src2;
	unsigned int	d;

	d = va_arg(tab->arg, unsigned int);
	src2 = ft_eval_precision_dec(tab, d);
	if (tab->width)
	{
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", ft_strlen(src2));
		if (tab->zero && tab->pnt == 0)
			res = ft_str_padding(tab->width, src2, "0", 0);
		if (tab->zero && tab->pnt == 1)
			res = ft_str_padding(tab->width, src2, " ", 0);
		if (!tab->dash && !tab->zero)
			res = ft_str_padding(tab->width, src2, " ", 0);
		free(src2);
	}
	if (!tab->width)
		res = src2;
	return (ft_pf_putstr(res));
}
