/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:23:11 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:23:16 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_digit_out(t_printf *p, t_spec *spcs)
{
	char				*s;
	long long int		arg;

	arg = ft_cast_d(p, spcs);
	s = pf_itoa(arg < 0 ? -arg : arg);
	if (spcs->percision < 0 && spcs->minus == 0 && spcs->zero
				&& ((int)(spcs->width - ft_strlen(s)) > 0))
	{
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), '0', 1);
		if (ft_signing(arg, spcs))
			s[0] = ft_signing(arg, spcs);
	}
	else
	{
		if (spcs->percision == 0 && arg == 0)
			s[0] = '\0';
		s = ft_join_n_ch_l(s, spcs->percision - ft_strlen(s), '0', 1);
		s = ft_join_n_ch_l(s, 1, ft_signing(arg, spcs), 1);
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), ' ',
				(spcs->minus) ? 0 : 1);
	}
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}

long long int	ft_cast_d(t_printf *p, t_spec *spcs)
{
	if (spcs->size == ll)
		return (va_arg(p->ap, long long int));
	if (spcs->size == l)
		return (va_arg(p->ap, long int));
	if (spcs->size == hh)
		return ((signed char)va_arg(p->ap, int));
	if (spcs->size == h)
		return ((signed short int)va_arg(p->ap, int));
	if (spcs->size == z)
		return ((size_t)va_arg(p->ap, unsigned long long int));
	if (spcs->size == j)
		return ((intmax_t)va_arg(p->ap, unsigned long long int));
	return (va_arg(p->ap, int));
}

char			*pf_itoa(unsigned long long int i)
{
	char						*res;
	unsigned long long int		k;
	int							len;

	len = 1;
	k = i;
	while (k /= 10)
		len++;
	if ((res = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_bzero(res, len + 1);
	if (i == 0)
		res[0] = '0';
	while (i)
	{
		res[--len] = i % 10 + 48;
		i = i / 10;
	}
	return (res);
}

char			ft_signing(long long int arg, t_spec *spcs)
{
	char	c;

	c = 0;
	if (arg < 0)
		c = '-';
	if (arg > -1 && spcs->space)
		c = ' ';
	if (arg > -1 && spcs->plus)
		c = '+';
	return (c);
}

char			*ft_join_n_ch_l(char *src, int n, char c, int left)
{
	int		len;
	char	*tmp;
	char	*res;
	int		i;

	if (!src)
		return (NULL);
	if (n < 1 || c == 0)
		return (src);
	len = ft_strlen(src);
	tmp = ft_strnew(n);
	i = 0;
	while (i < n)
		tmp[i++] = c;
	if (left)
		res = ft_strjoin(tmp, src);
	else
		res = ft_strjoin(src, tmp);
	free(tmp);
	free(src);
	return (res);
}
