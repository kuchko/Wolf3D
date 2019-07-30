/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:55:21 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 20:55:24 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct			s_printf
{
	int					i;
	int					count;
	char				*f;
	va_list				ap;
}						t_printf;

typedef enum			e_size
{
	not, hh, h, l, ll, L, j, z
}						t_size;

typedef struct			s_specificators
{
	t_size				size;
	unsigned int		minus : 1;
	unsigned int		plus : 1;
	unsigned int		hash : 1;
	unsigned int		zero : 1;
	unsigned int		space : 1;
	unsigned int		floatisneg : 1;
	int					width;
	int					percision;
}						t_spec;

int						ft_printf(const char *format, ...);

void					ft_spec_work(t_printf *p, t_spec *spcs);
void					tmp_put_params(t_spec *spcs);
void					ft_type_work(t_printf *p, t_spec *spcs);

void					ft_spec_init(t_spec *flags);
void					ft_flags_find(t_printf *p, t_spec *spcs);
void					ft_width_find(t_printf *p, t_spec *spcs);
void					ft_percision_find(t_printf *p, t_spec *spcs);
void					ft_size_find(t_printf *p, t_spec *spcs);

int						ft_digit_out(t_printf *p, t_spec *spcs);
long long int			ft_cast_d(t_printf *p, t_spec *spcs);
char					*pf_itoa(unsigned long long int i);
char					ft_signing(long long int arg, t_spec *spcs);
char					*ft_join_n_ch_l(char *src, int n, char c, int left);

int						ft_o_out(t_printf *p, t_spec *spcs);
int						ft_x_out(t_printf *p, t_spec *spcs, char c);
unsigned long long int	ft_cast_ox(t_printf *p, t_spec *spcs);
char					*pf_itoa_base(unsigned long long int i, char c);
char					*ft_join_0x(char *src, char c);

int						ft_s_out(t_printf *p, t_spec *spcs);
int						ft_c_out(t_printf *p, t_spec *spcs);
int						ft_p_out(t_printf *p, t_spec *spcs);
int						ft_end_out(t_printf *p, t_spec *spcs);
char					*ft_strncrop(char *s, int n);

int						ft_u_out(t_printf *p, t_spec *spcs);

int						ft_f_out(t_printf *p, t_spec *spcs);
char					*ft_float_overflow(t_printf *p, t_spec *spcs,
														long double arg);
char					ft_floatsign(long double arg, t_spec *spcs);
char					*ft_float_num(t_spec *spcs, long double arg);

long double				ft_f_round(long double arg, int perc);
char					*ft_str_before_dot(long double arg);
long double				ft_eps(long double arg);
char					*ft_str_after_dot(long double arg, int perc);
char					*ft_strjoinfree(char *s1, char *s2);

int						ft_iputstr(char *s);
int						ft_iputchar(char c);

#endif
