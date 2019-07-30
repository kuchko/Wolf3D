/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:23:59 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:24:07 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_f_out(t_printf *p, t_spec *spcs)
{
	char		*s;
	long double	arg;
	int			res;
	__uint128_t	*u;

	arg = (spcs->size == L) ? va_arg(p->ap, long double) :
											(double)va_arg(p->ap, double);
	u = (__uint128_t*)&arg;
	spcs->floatisneg = (*u << (127 - 79)) >> 127;
	if (arg != arg || (arg != 0 && arg * 2 == arg))
		s = ft_float_overflow(p, spcs, arg);
	else
		s = ft_float_num(spcs, arg);
	res = ft_iputstr(s);
	free(s);
	return (res);
}

char	*ft_float_overflow(t_printf *p, t_spec *spcs, long double arg)
{
	char *s;

	if (arg != arg)
	{
		s = (p->f[p->i] == 'F') ? ft_strdup("NAN") : ft_strdup("nan");
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
											' ', (spcs->minus) ? 0 : 1);
	}
	else
	{
		s = (p->f[p->i] == 'F') ? ft_strdup("INF") : ft_strdup("inf");
		s = ft_join_n_ch_l(s, 1, ft_floatsign(arg, spcs), 1);
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
											' ', (spcs->minus) ? 0 : 1);
	}
	return (s);
}

char	*ft_float_num(t_spec *spcs, long double arg)
{
	char		*s;
	long double	tmp;

	spcs->percision = (spcs->percision == -1 ? 6 : spcs->percision);
	tmp = ft_f_round(spcs->floatisneg ? -arg : arg, spcs->percision);
	s = ft_str_before_dot(tmp);
	if (spcs->hash || spcs->percision > 0)
		s = ft_join_n_ch_l(s, 1, '.', 0);
	if (spcs->percision > 0)
		s = ft_strjoinfree(s, ft_str_after_dot(tmp, spcs->percision));
	if (spcs->minus == 0 && spcs->zero &&
								((int)(spcs->width - ft_strlen(s)) > 0))
	{
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), '0', 1);
		if (ft_floatsign(arg, spcs))
			s[0] = ft_floatsign(arg, spcs);
	}
	else
	{
		s = ft_join_n_ch_l(s, 1, ft_floatsign(arg, spcs), 1);
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), ' ',
													(spcs->minus) ? 0 : 1);
	}
	return (s);
}

char	ft_floatsign(long double arg, t_spec *spcs)
{
	char	c;

	c = 0;
	if (spcs->floatisneg)
		c = '-';
	if (arg >= 0 && spcs->space)
		c = ' ';
	if (arg >= 0 && spcs->plus)
		c = '+';
	return (c);
}
