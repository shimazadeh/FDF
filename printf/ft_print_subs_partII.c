/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_subs_partII.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:22:51 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/04 18:22:26 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printhex_low(t_print	*tab)
{
	char	*res;
	char	*src;
	char	*src2;

	src = ft_pf_nbr_hex(va_arg(tab->arg, unsigned int), "0123456789abcdef");
	src2 = ft_eval_flags_ex(tab, src, "0x");
	res = ft_eval_width_ex(tab, src2);
	return (ft_pf_putstr(res));
}

int	ft_printhex_up(t_print	*tab)
{
	char	*res;
	char	*src;
	char	*src2;

	src = ft_pf_nbr_hex(va_arg(tab->arg, unsigned int), "0123456789ABCDEF");
	src2 = ft_eval_flags_ex(tab, src, "0X");
	res = ft_eval_width_ex(tab, src2);
	return (ft_pf_putstr(res));
}

int	ft_printpointer(t_print	*tab)
{
	char				*res;
	char				*src;
	char				*src2;
	unsigned long int	d;

	d = (unsigned long)va_arg(tab->arg, void *);
	src = ft_pf_nbr_hex(d, "0123456789abcdef");
	src2 = ft_str_multi_padding_left(src, "0x");
	if (tab->width)
	{
		if (tab->dash)
			res = ft_str_padding(tab->width, src2, " ", ft_strlen(src2));
		if (!tab->dash)
			res = ft_str_padding(tab->width, src2, " ", 0);
		free(src2);
	}
	if (!tab->width)
		res = src2;
	free(src);
	return (ft_pf_putstr(res));
}

int	ft_print_percent(t_print *tab)
{
	char	*res;
	char	*src;

	src = "%";
	if (tab->width)
	{
		if (tab->dash)
			res = ft_str_padding(tab->width, src, " ", 1);
		if (tab->zero)
			res = ft_str_padding(tab->width, src, "0", 0);
		if (!tab->dash && !tab->zero)
			res = ft_str_padding(tab->width, src, " ", 0);
		return (ft_pf_putstr(res));
	}
	else
		res = src;
	return (write(1, "%", 1));
}
