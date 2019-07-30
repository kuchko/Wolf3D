/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:25:40 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:25:42 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf	p;
	t_spec		spcs;

	p.count = 0;
	p.f = (char*)format;
	va_start(p.ap, format);
	p.i = -1;
	while (p.f[++p.i])
	{
		if (p.f[p.i] == '%')
		{
			p.i++;
			ft_spec_work(&p, &spcs);
			ft_type_work(&p, &spcs);
		}
		else
			p.count += write(1, &p.f[p.i], 1);
	}
	va_end(p.ap);
	return (p.count);
}

void	ft_spec_work(t_printf *p, t_spec *spcs)
{
	ft_spec_init(spcs);
	while (p->f[p->i] && ft_strchr("-+ #0*123456789.hlLzj", p->f[p->i]))
	{
		ft_flags_find(p, spcs);
		ft_width_find(p, spcs);
		ft_percision_find(p, spcs);
		ft_size_find(p, spcs);
	}
}

void	tmp_put_params(t_spec *spcs)
{
	ft_printf("\n fl = %d, - %d, + %d, # %d, zero %d",
	spcs->size, spcs->minus, spcs->plus, spcs->hash, spcs->zero);
	ft_printf(" ' ' %d, w = %d, perc = %d, size = %d\n",
	spcs->space, spcs->width, spcs->percision, spcs->size);
}

void	ft_type_work(t_printf *p, t_spec *sp)
{
	if (p->f[p->i] == 'd' || p->f[p->i] == 'i')
		p->count += ft_digit_out(p, sp);
	else if (p->f[p->i] == 'D' && (sp->size = (sp->size < l ? l : sp->size)))
		p->count += ft_digit_out(p, sp);
	else if (p->f[p->i] == 'o')
		p->count += ft_o_out(p, sp);
	else if (p->f[p->i] == 'O' && (sp->size = (sp->size < l ? l : sp->size)))
		p->count += ft_o_out(p, sp);
	else if (p->f[p->i] == 'x' || p->f[p->i] == 'X')
		p->count += ft_x_out(p, sp, p->f[p->i]);
	else if (p->f[p->i] == 's' || p->f[p->i] == 'S')
		p->count += ft_s_out(p, sp);
	else if (p->f[p->i] == 'c' || p->f[p->i] == 'C')
		p->count += ft_c_out(p, sp);
	else if (p->f[p->i] == 'u')
		p->count += ft_u_out(p, sp);
	else if (p->f[p->i] == 'U' && (sp->size = (sp->size < l ? l : sp->size)))
		p->count += ft_u_out(p, sp);
	else if (p->f[p->i] == 'p')
		p->count += ft_p_out(p, sp);
	else if (p->f[p->i] == 'f' || p->f[p->i] == 'F')
		p->count += ft_f_out(p, sp);
	else
		p->count += ft_end_out(p, sp);
}
