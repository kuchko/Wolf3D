/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_iputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 18:24:44 by okuchko           #+#    #+#             */
/*   Updated: 2019/03/07 18:24:48 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_iputchar(char c)
{
	return (write(1, &c, 1));
}

int		ft_iputstr(char *s)
{
	int len;

	if (!s || *s == '\0')
		return (0);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
