/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:46:47 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/02 15:25:29 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	*ft_pf_evalflag(t_print *tab, const char c)
{
	if (c == '-')
		tab->dash = 1;
	if (c == '.')
		tab->pnt = 1;
	if (c == '#')
		tab->hashtag = 1;
	if (c == ' ')
		tab->space = 1;
	if (c == '%')
		tab->perc = 1;
	if (c == '+')
		tab->sign = 1;
	if (c == '0')
		tab->zero = 1;
	return (tab);
}

int	ft_str_count(const char *str)
{
	int		size;
	int		j;
	int		i;
	char	*s;

	s = "dcuisxXp.%";
	size = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (s[j])
		{
			if (str[i] == s[j])
				return (size);
			j++;
		}
		size++;
		i++;
	}
	return (size);
}

void	*ft_width_precision(t_print *tab, const char **str, int flag)
{
	char	*buff;
	int		result;
	int		j;
	int		size;

	j = 0;
	size = ft_str_count(*str);
	buff = (char *) malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (NULL);
	while (!ft_strchr_boolean(**str, "dsicuxXp.%"))
	{
		buff[j] = **str;
		(*str)++;
		j++;
	}
	buff[j] = '\0';
	result = ft_atoi(buff);
	if (flag == 0)
		tab->width = result;
	else
		tab->precision = result;
	free (buff);
	return (0);
}

void	*ft_update_tab(t_print *tab, const char **str)
{
	while (!ft_strchr_boolean(**str, "dicusxXp%"))
	{
		if (ft_isdigit(**str) == 0)
			ft_pf_evalflag(tab, **str);
		if (ft_isdigit(**str) == 1)
			ft_width_precision(tab, str, 0);
		if (**str == '.')
		{
			tab->pnt = 1;
			(*str)++;
			ft_width_precision(tab, str, 1);
		}
		if (!ft_strchr_boolean(**str, "dicusxXp%"))
			(*str)++;
	}
	if (tab->space && tab->sign)
		tab->space = 0;
	if (tab->dash && tab->zero)
		tab->zero = 0;
	return (0);
}
