/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:21:24 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:21:30 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print_color(int color)
{
	int alfa;
	int r;
	int g;
	int b;

	alfa = ((color & 0xFF000000) >> 24);
	r = ((color & 0xFF0000) >> 16);
	g = ((color & 0xFF00) >> 8);
	b = color & 0xFF;
	ft_printf("color %x = %x, %x, %x, %x;\n", color, alfa, r, g, b);
}

int		change_color_rgb(int color, int step_x, int step_y, int alfa_step)
{
	int alfa;
	int r;
	int g;
	int b;

	alfa = alfa_step % 256;
	r = ft_abs(((color & 0xFF0000) >> 16) + step_x) % 256;
	g = ft_abs(((color & 0xFF00) >> 8) + step_y) % 256;
	b = ft_abs((color & 0xFF) + step_x + step_y) % 256;
	return ((alfa << 24) | (r << 16) | (g << 8) | b);
}

void	ft_putpixel(t_global *g, int x, int y, int color)
{
	int	*i;

	if (x > -1 && x < WIDTH && y > -1 && y < HIGHT)
	{
		i = (int*)g->adr;
		i[y * WIDTH + x] = color;
	}
}

void	ft_put_v_line(t_global *g, int x, int color)
{
	int y;

	y = g->w.line_start;
	while (y <= g->w.line_end)
		ft_putpixel(g, x, y++, color);
}
