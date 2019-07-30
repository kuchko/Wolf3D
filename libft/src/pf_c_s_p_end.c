/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c_s_p_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:55:14 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 21:55:18 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_s_out(t_printf *p, t_spec *spcs)
{
	char					*s;
	unsigned long long int	arg;

	s = va_arg(p->ap, char*);
	if (s == NULL)
		s = "(null)";
	s = ft_strdup(s);
	if (spcs->percision > -1)
		s = ft_strncrop(s, spcs->percision);
	s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
		(spcs->zero && !spcs->minus) ? '0' : ' ', (spcs->minus) ? 0 : 1);
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}

int		ft_c_out(t_printf *p, t_spec *spcs)
{
	char					*s;
	unsigned long long int	arg;

	s = ft_strnew(1);
	s[0] = (char)va_arg(p->ap, int);
	if (s[0] == 0)
	{
		s = ft_join_n_ch_l(s, spcs->width - 1,
			(spcs->zero && !spcs->minus) ? '0' : ' ', 1);
		spcs->minus ? ft_putchar('\0') : ft_printf("%s", s);
		spcs->minus ? ft_printf("%s", s) : ft_putchar('\0');
		arg = ft_strlen(s) + 1;
	}
	else
	{
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
			(spcs->zero && !spcs->minus) ? '0' : ' ', (spcs->minus) ? 0 : 1);
		arg = ft_iputstr(s);
	}
	free(s);
	return (arg);
}

int		ft_p_out(t_printf *p, t_spec *spcs)
{
	char					*s;
	unsigned long long int	arg;

	spcs->size = ll;
	arg = ft_cast_ox(p, spcs);
	s = pf_itoa_base(arg, 'x');
	if (spcs->percision == 0 && arg == 0)
		s[0] = '\0';
	s = ft_join_n_ch_l(s, spcs->percision - ft_strlen(s), '0', 1);
	if (spcs->zero && !spcs->minus && spcs->percision < 0)
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s) - 2, '0', 1);
	s = ft_join_0x(s, 'x');
	s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), ' ',
											(spcs->minus) ? 0 : 1);
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}

int		ft_end_out(t_printf *p, t_spec *spcs)
{
	char					*s;
	unsigned long long int	arg;

	s = ft_strnew(1);
	s[0] = p->f[p->i];
	if (s[0] == 0)
	{
		p->i--;
		arg = 0;
	}
	else
	{
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
		(spcs->zero && !spcs->minus) ? '0' : ' ', (spcs->minus) ? 0 : 1);
		arg = ft_iputstr(s);
	}
	free(s);
	return (arg);
}

char	*ft_strncrop(char *s, int n)
{
	int		len;
	char	*res;

	len = ft_strlen(s);
	if (n >= len || n < 0)
		return (s);
	res = ft_strnew(n);
	if (n > 0)
		ft_strncpy(res, s, n);
	free(s);
	return (res);
}
