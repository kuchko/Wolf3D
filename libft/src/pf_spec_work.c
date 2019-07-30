/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_spec_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 21:10:05 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 21:10:12 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_spec_init(t_spec *spcs)
{
	ft_bzero(spcs, sizeof(t_spec));
	spcs->size = not;
	spcs->percision = -1;
}

void	ft_flags_find(t_printf *p, t_spec *spcs)
{
	while (p->f[p->i] && (p->f[p->i] == '-' || p->f[p->i] == '+' ||
		p->f[p->i] == '#' || p->f[p->i] == ' ' || p->f[p->i] == '0'))
	{
		if (p->f[p->i] == '-')
			spcs->minus = 1;
		if (p->f[p->i] == '+')
			spcs->plus = 1;
		if (p->f[p->i] == '#')
			spcs->hash = 1;
		if (p->f[p->i] == '0')
			spcs->zero = 1;
		if (p->f[p->i] == ' ')
			spcs->space = 1;
		p->i++;
	}
}

void	ft_width_find(t_printf *p, t_spec *spcs)
{
	if (p->f[p->i] == '*')
	{
		spcs->width = va_arg(p->ap, int);
		if (spcs->width < 0)
		{
			spcs->minus = 1;
			spcs->width *= -1;
		}
		p->i++;
	}
	else if (p->f[p->i] && (p->f[p->i] >= '0') && (p->f[p->i] <= '9'))
	{
		spcs->width = 0;
		while (p->f[p->i] && (p->f[p->i] >= '0') && (p->f[p->i] <= '9'))
		{
			spcs->width = 10 * spcs->width + p->f[p->i] - 48;
			p->i++;
		}
	}
}

void	ft_percision_find(t_printf *p, t_spec *spcs)
{
	if (p->f[p->i] && p->f[p->i] == '.')
	{
		p->i++;
		spcs->percision = 0;
		if (p->f[p->i] == '*')
		{
			spcs->percision = va_arg(p->ap, int);
			p->i++;
		}
		else
		{
			while (p->f[p->i] && (p->f[p->i] >= '0') && (p->f[p->i] <= '9'))
			{
				spcs->percision = 10 * spcs->percision + p->f[p->i] - 48;
				p->i++;
			}
		}
	}
}

void	ft_size_find(t_printf *p, t_spec *spcs)
{
	if (p->f[p->i] && ft_strchr("hlLzj", p->f[p->i]))
	{
		if (spcs->size < hh && p->f[p->i + 1] &&
				p->f[p->i] == 'h' && p->f[p->i + 1] == 'h' && ++p->i)
			spcs->size = hh;
		else if (spcs->size < h && p->f[p->i] == 'h')
			spcs->size = h;
		else if (spcs->size < ll && p->f[p->i + 1] &&
				p->f[p->i] == 'l' && p->f[p->i + 1] == 'l' && ++p->i)
			spcs->size = ll;
		else if (spcs->size < l && p->f[p->i] == 'l')
			spcs->size = l;
		else if (spcs->size < L && p->f[p->i] == 'L')
			spcs->size = L;
		else if (spcs->size < j && p->f[p->i] == 'j')
			spcs->size = j;
		else if (spcs->size < z && p->f[p->i] == 'z')
			spcs->size = z;
		p->i++;
	}
}
