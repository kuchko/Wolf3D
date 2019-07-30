/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floatnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:24:28 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:24:32 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		ft_f_round(long double arg, int perc)
{
	int			i;
	long double	eps;
	long double	tmp;

	i = perc;
	tmp = arg;
	while (i > 0 && (tmp != 2 * tmp))
	{
		tmp *= 10;
		i--;
	}
	if (tmp == 2 * tmp)
		return (arg);
	eps = ft_eps(tmp);
	if (eps == 0.5)
		tmp = tmp + ((int)tmp % 2 ? 0.5 : -0.5);
	else
		tmp = (eps > 0.5 ? tmp + 0.5 : tmp);
	while (i++ < perc)
		tmp /= 10;
	return (tmp);
}

char			*ft_str_before_dot(long double arg)
{
	char		*s;
	int			i;
	int			k;
	long double	tmp;
	long double	ter;

	tmp = arg;
	i = 0;
	ter = 1;
	if (tmp < 1)
		return (ft_strdup("0"));
	while (tmp >= 1 && ++i)
	{
		tmp = tmp / 10;
		ter *= 10;
	}
	s = ft_strnew(i);
	k = 0;
	while (ter > 1 && k < i)
	{
		ter = ter / 10;
		s[k] = 48 + (int)(arg / ter);
		arg -= (s[k++] - 48) * ter;
	}
	return (s);
}

char			*ft_str_after_dot(long double arg, int perc)
{
	int			i;
	char		*s;
	long double	eps;

	if (perc < 1)
		return (ft_strdup("\0"));
	eps = ft_eps(arg);
	s = ft_strnew(perc);
	i = 0;
	while (i < perc)
	{
		eps *= 10;
		s[i++] = 48 + (int)(eps);
		eps -= (int)(eps);
	}
	return (s);
}

long double		ft_eps(long double arg)
{
	long double	tmp;
	long double	ter;

	tmp = arg;
	ter = 1;
	while (tmp >= 1)
	{
		tmp = tmp / 10;
		ter *= 10;
	}
	while (ter > 1)
	{
		ter = ter / 10;
		arg -= ((int)(arg / ter)) * ter;
	}
	return (arg);
}

char			*ft_strjoinfree(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (ft_strdup("\0"));
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	res = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (res == NULL)
		return (NULL);
	res = ft_strcpy(res, s1);
	res = ft_strcat(res, s2);
	free(s1);
	free(s2);
	return (res);
}
