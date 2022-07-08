/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:00 by shabibol          #+#    #+#             */
/*   Updated: 2022/04/04 16:13:56 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_print
{
	va_list		arg;
	int			width;
	int			precision;
	int			zero;
	int			dash;
	int			pnt;
	int			hashtag;
	int			space;
	int			sign;
	int			perc;
	int			width_flag;
	int			len_print;
}t_print;

int			ft_isdigit(int c);
int			ft_get_digits_hex(unsigned long long c);
int			ft_get_digits(long int c);
int			ft_atoi(const char *str);
int			ft_str_count(const char *str);
int			ft_eval_format(t_print *tab, const char **str);
int			ft_strchr_boolean(char c, char *str);
int			ft_strlen(char *str);
int			ft_printf(const char *str, ...);
int			ft_pf_putchar(const char c);
int			ft_pf_putstr(char *s);

char		*ft_strndup(char *src, int size);
char		*ft_itoa(long long int d);
char		*ft_itoa_sign(long int d);
char		*ft_str_cut(t_print *tab, char *str);
char		*ft_str_multi_padding_left(char *src, char *padding);
char		*ft_str_padding(int width, char *src, char *padding, int start);
char		*ft_int_add_char(long long int d, char c);
char		*ft_pf_nbr_hex(unsigned long long nbr, char *ref);

t_print		*ft_pf_evalflag(t_print *tab, const char c);
t_print		*ft_initialize_flags(t_print *tab);

void		*ft_width_precision(t_print *tab, const char **str, int flag);

void		*ft_update_tab(t_print *tab, const char **str);
void		ft_pf_putchar_width(char c, int size);

int			ft_printchar(t_print *tab);
int			ft_printstr(t_print *tab);
int			ft_printinteger(t_print *tab);
int			ft_printdecimal(t_print *tab);
int			ft_printhex_low(t_print *tab);
int			ft_printhex_up(t_print *tab);
int			ft_printpointer(t_print *tab);
int			ft_print_percent(t_print *tab);

int			ft_pf_putchar_addr(char *c);
int			ft_max_width(int width, char *src);
int			ft_max_precision(t_print *tab, char *src);
int			ft_pf_putstr_char(char *s);
char		*ft_char_padding(t_print *tab, char *src, char *padding);
int			ft_pf_putstr_char_null(t_print *tab, char *s);

char		*ft_eval_flags_int(t_print *tab, int src);
char		*ft_eval_flags_ex(t_print *tab, char *src, char *x);
char		*ft_eval_sign(t_print *tab, int src);
char		*ft_eval_space(t_print *tab, int src);

char		*ft_assign_null(t_print *tab);
char		*ft_eval_precision_int(t_print *tab, int src);
char		*ft_eval_precision_ex(t_print *tab, char *src);
char		*ft_eval_width_ex(t_print *tab, char *src);
char		*ft_eval_precision_dec(t_print *tab, unsigned int d);
char		*ft_eval_width_str(t_print *tab, char *src2);

int			ft_eval_char_null(t_print *tab, char src);
#endif
