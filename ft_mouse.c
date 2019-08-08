/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:21:12 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:21:14 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_mouse_press(int key, int x, int y, t_global *g)
{
	x = y;

	if (key == ZOOM_IN && g->w.plane_y > 0.3)
	{
		// g->w.ampl_wall_high -= 0.02;
		g->w.plane_y -= 0.02;
		ft_printf("A %f, PL %f\n", g->w.ampl_wall_high, g->w.plane_y);
	}
	if (key == ZOOM_OUT && g->w.plane_y < 1.0)
	{
		// g->w.ampl_wall_high += 0.02;
		g->w.plane_y += 0.02;
		ft_printf("A %f, PL %f\n", g->w.ampl_wall_high, g->w.plane_y);
	}
	// if (key == ZOOM_IN || key == ZOOM_OUT)
	// {
	// 	sign = key == ZOOM_IN ? 1.0 : -1.0;
	// 	g->fr.move_y += sign * ((2 * y - IMG_HIGHT) / (double)IMG_HIGHT - (2 *
	// 		y - IMG_HIGHT) / (double)IMG_HIGHT / g->fr.zoom_step) / g->fr.zoom;
	// 	g->fr.move_x += 1.5 * sign * ((2 * x - IMG_WIDTH) / (double)IMG_WIDTH -
	// 	(2 * x - IMG_WIDTH) / (double)IMG_WIDTH / g->fr.zoom_step) / g->fr.zoom;
	// 	if (key == ZOOM_IN)
	// 		g->fr.zoom *= g->fr.zoom_step;
	// 	else if (g->fr.zoom > 0.01)
	// 		g->fr.zoom /= g->fr.zoom_step;
	// }
	// else if (key == MOUSE_LEFT || key == MOUSE_RIGHT)
	// {
	// 	g->fr.flag_move = (key == MOUSE_LEFT) ? 1 : 0;
	// 	g->fr.flag_color_move = (key == MOUSE_RIGHT) ? 1 : 0;
	// 	g->fr.x_pre = x;
	// 	g->fr.y_pre = y;
	// }

	// ft_re_draw(g);
	return (0);
}

// int		ft_mouse_release(int key, int x, int y, t_global *g)
// {
// 	x = y;
// 	if (key == MOUSE_LEFT || key == MOUSE_RIGHT)
// 	{
// 		g->fr.flag_move = 0;
// 		g->fr.flag_color_move = 0;
// 	}
// 	return (0);
// }

// int		ft_mouse_move(int x, int y, t_global *g)
// {
// 	if ((g->fr.flag_move == 1 || g->fr.flag_color_move == 1)
// 		&& x > -1 && x < IMG_WIDTH && y > -1 && y < IMG_HIGHT)
// 	{
// 		if (g->fr.flag_move == 1)
// 		{
// 			g->fr.stp_re += 2.0 * (x - g->fr.x_pre) / IMG_WIDTH / g->fr.zoom;
// 			g->fr.stp_im += 2.0 * (y - g->fr.y_pre) / IMG_HIGHT / g->fr.zoom;
// 		}
// 		else
// 		{
// 			g->fr.c_step_x += (x - g->fr.x_pre) / 2;
// 			g->fr.c_step_y += (y - g->fr.y_pre) / 2;
// 		}
// 		g->fr.x_pre = x;
// 		g->fr.y_pre = y;
// 		ft_re_draw(g);
// 	}
// 	return (0);
// }
