/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:11:37 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/02 18:59:38 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_strchr_boolean(char c, char *str)
{
	while (*str && *str != c)
		str++;
	if (*str == c)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	signed int		result;
	signed int		sign;
	unsigned int	i;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int	ft_get_digits(long int n)
{
	int	size;

	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(long long int n)
{
	char		*result;
	long int	num;
	long int	digit;

	num = n;
	digit = ft_get_digits(n);
	if (n <= 0)
	{
		num *= -1;
		digit++;
	}
	result = (char *)malloc(sizeof(char) * (digit + 1));
	if (!result)
		return (NULL);
	result[digit] = '\0';
	while (digit--)
	{
		result[digit] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

char	*ft_assign_null(t_print *tab)
{
	char	*src;
	char	*dest;
	int		i;
	char	*src2;
	char	*res;

	i = 0;
	src = "(null)";
	dest = (char *)malloc(sizeof(char) * 7);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	src2 = ft_str_cut(tab, dest);
	res = ft_eval_width_str(tab, src2);
	free(dest);
	return (res);
}
