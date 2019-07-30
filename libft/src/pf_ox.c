/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ox.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:25:00 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:25:05 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_o_out(t_printf *p, t_spec *spcs)
{
	char						*s;
	unsigned long long int		arg;

	arg = ft_cast_ox(p, spcs);
	s = pf_itoa_base(arg, 'o');
	if (spcs->percision == 0 && arg == 0)
		s[0] = '\0';
	s = ft_join_n_ch_l(s, spcs->percision - ft_strlen(s), '0', 1);
	if (spcs->hash && s[0] != '0')
		s = ft_join_n_ch_l(s, 1, '0', 1);
	if (spcs->zero && !spcs->minus && spcs->percision < 0)
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), '0', 1);
	s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), ' ',
													(spcs->minus) ? 0 : 1);
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}

int						ft_x_out(t_printf *p, t_spec *spcs, char c)
{
	char						*s;
	unsigned long long int		arg;

	arg = ft_cast_ox(p, spcs);
	s = pf_itoa_base(arg, c);
	if (spcs->percision == 0 && arg == 0)
		s[0] = '\0';
	s = ft_join_n_ch_l(s, spcs->percision - ft_strlen(s), '0', 1);
	if (spcs->zero && !spcs->minus && spcs->percision < 0)
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s) -
				((spcs->hash && arg != 0 && s[0] != '\0') ? 2 : 0), '0', 1);
	if (spcs->hash && arg != 0 && s[0] != '\0')
		s = ft_join_0x(s, c);
	s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), ' ',
													(spcs->minus) ? 0 : 1);
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}

unsigned long long int	ft_cast_ox(t_printf *p, t_spec *spcs)
{
	if (spcs->size == ll)
		return (va_arg(p->ap, unsigned long long int));
	if (spcs->size == l)
		return (va_arg(p->ap, unsigned long int));
	if (spcs->size == hh)
		return ((unsigned char)va_arg(p->ap, unsigned int));
	if (spcs->size == h)
		return ((unsigned short int)va_arg(p->ap, unsigned int));
	if (spcs->size == z)
		return ((size_t)va_arg(p->ap, unsigned long long int));
	if (spcs->size == j)
		return ((intmax_t)va_arg(p->ap, unsigned long long int));
	return ((unsigned int)va_arg(p->ap, unsigned int));
}

char					*pf_itoa_base(unsigned long long int i, char c)
{
	char						*res;
	unsigned long long int		k;
	int							len;
	int							base;

	base = (c == 'o' ? 8 : 16);
	len = 1;
	k = i;
	while (k /= base)
		len++;
	if ((res = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_bzero(res, len + 1);
	if (i == 0)
		res[0] = '0';
	while (i)
	{
		if (c == 'X')
			res[--len] = i % base + (i % base > 9 ? 55 : 48);
		else
			res[--len] = i % base + (i % base > 9 ? 87 : 48);
		i = i / base;
	}
	return (res);
}

char					*ft_join_0x(char *src, char c)
{
	char	*tmp;
	char	*res;

	if (!src)
		return (NULL);
	if (c == 'x')
		tmp = ft_strdup("0x");
	else
		tmp = ft_strdup("0X");
	if (!tmp)
		return (NULL);
	if (!(res = ft_strjoin(tmp, src)))
		return (NULL);
	free(tmp);
	free(src);
	return (res);
}
