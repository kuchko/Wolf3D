/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:20:42 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:20:44 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// static int	ft_keys_select(int key, t_global *g)
// {
// 	if (key > 17 && key < 22)
// 		g->fractol_select = key - 17;
// 	else if (key == 23)
// 		g->fractol_select = 5;
// 	else if (key == 22)
// 		g->fractol_select = 6;
// 	else if (key == 26)
// 		g->fractol_select = 7;
// 	else if (key == 28)
// 		g->fractol_select = 8;
// 	if (key == RELOAD || (key > 17 && key < 23) || key == 26 || key == 28)
// 		globals_init(g);
// 	return (0);
// }

// static int	ft_keys_color(int key, t_global *g)
// {
// 	if (key == COLOR_PLUS)
// 	{
// 		g->fr.c_step_x += 1;
// 		g->fr.c_step_y += 1;
// 	}
// 	else if (key == COLOR_MINUS)
// 	{
// 		g->fr.c_step_x -= 1;
// 		g->fr.c_step_y -= 1;
// 	}
// 	else if (key == ALPHA_PLUS && g->fr.a_s < 255)
// 		g->fr.a_s += 5;
// 	else if (key == ALPHA_MINUS && g->fr.a_s > 4)
// 		g->fr.a_s -= 5;
// 	else
// 		ft_keys_select(key, g);
// 	return (0);
// }

int			ft_keys(int key, t_global *g)
{
	if (key == ESC)
	{
		system("leaks fractol > leaks");
		exit(0);
	}
	// else if (key == MOVE_UP)
	// 	g->fr.move_y -= 0.2 / g->fr.zoom;
	// else if (key == MOVE_DOWN)
	// 	g->fr.move_y += 0.2 / g->fr.zoom;
	// else if (key == MOVE_LEFT)
	// 	g->fr.move_x -= 0.2 / g->fr.zoom;
	// else if (key == MOVE_RIGHT)
	// 	g->fr.move_x += 0.2 / g->fr.zoom;
	// else if (key == ITER_PLUS)
	// 	g->fr.max_iterations += 1;
	// else if (key == ITER_MINUS && g->fr.max_iterations > 1)
	// 	g->fr.max_iterations -= 1;
	// else if (key == CENTER_ZOOM_IN)
	// 	g->fr.zoom += 0.2 * g->fr.zoom;
	// else if (key == CENTER_ZOOM_OUT)
	// 	g->fr.zoom -= 0.2 * g->fr.zoom;
	// else
	// 	ft_keys_color(key, g);
	ft_re_draw(g);
	return (0);
}
