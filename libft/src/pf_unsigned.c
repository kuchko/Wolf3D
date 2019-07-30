/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:51:38 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 20:51:48 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_u_out(t_printf *p, t_spec *spcs)
{
	char						*s;
	unsigned long long int		arg;

	arg = ft_cast_ox(p, spcs);
	s = pf_itoa(arg);
	if (spcs->percision == 0 && arg == 0)
		s[0] = '\0';
	s = ft_join_n_ch_l(s, spcs->percision - ft_strlen(s), '0', 1);
	if (spcs->zero && !spcs->minus && spcs->percision < 0)
		s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s), '0', 1);
	s = ft_join_n_ch_l(s, spcs->width - ft_strlen(s),
									' ', (spcs->minus) ? 0 : 1);
	arg = ft_iputstr(s);
	free(s);
	return (arg);
}
