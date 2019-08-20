/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:41:06 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:41:10 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_and_side_distance_calc(int x, t_wolf *w)
{
	w->camera_x = 2 * x / (double)IMG_WIDTH - 1;
	w->ray_dir_x = w->dir_x + w->plane_x * w->camera_x;
	w->ray_dir_y = w->dir_y + w->plane_y * w->camera_x;
	w->map_x = (int)w->pos_x;
	w->map_y = (int)w->pos_y;
	w->delt_dst_x = fabs(1 / w->ray_dir_x);
	w->delt_dst_y = fabs(1 / w->ray_dir_y);
	w->hit = 0;
	if (w->ray_dir_x < 0 && (w->step_x = -1))
		w->side_dst_x = (w->pos_x - w->map_x) * w->delt_dst_x;
	else
	{
		w->step_x = 1;
		w->side_dst_x = (w->map_x + 1.0 - w->pos_x) * w->delt_dst_x;
	}
	if (w->ray_dir_y < 0 && (w->step_y = -1))
		w->side_dst_y = (w->pos_y - w->map_y) * w->delt_dst_y;
	else
	{
		w->step_y = 1;
		w->side_dst_y = (w->map_y + 1.0 - w->pos_y) * w->delt_dst_y;
	}
}

void	ft_dda_hit(t_wolf *w)
{
	while (w->hit == 0)
	{
		if (w->side_dst_x < w->side_dst_y)
		{
			w->side_dst_x += w->delt_dst_x;
			w->map_x += w->step_x;
			w->side = 0;
		}
		else
		{
			w->side_dst_y += w->delt_dst_y;
			w->map_y += w->step_y;
			w->side = 1;
		}
		w->map[w->map_x][w->map_y] > 0 ? w->hit = 1 : 0;
	}
	w->p_wall_dst = w->side == 0 ? (w->map_x - w->pos_x + (1 - w->step_x) / 2)
	/ w->ray_dir_x : (w->map_y - w->pos_y + (1 - w->step_y) / 2) / w->ray_dir_y;
	w->line_height = (int)(IMG_HIGHT / w->p_wall_dst);
	w->line_start = -w->line_height / 2 + IMG_HIGHT / 2;
	if (w->line_start < 0)
		w->line_start = 0;
	w->line_end = w->line_height / 2 + IMG_HIGHT / 2;
	if (w->line_end >= IMG_HIGHT)
		w->line_end = IMG_HIGHT - 1;
}

void	ft_colorized_environment(t_global *g, t_wolf *w, int x)
{
	int	clr;
	int y;

	if (w->map[w->map_x][w->map_y] == 1)
	{
		if (w->side == 0)
			clr = w->ray_dir_x > 0 ? 0xFF0000 : 0x00FF00;
		else
			clr = w->ray_dir_y > 0 ? 0xFFFFFF : 0x0000FF;
	}
	else
		clr = 0xFFFF00;
	if (w->side == 1)
		clr = (clr >> 1) & 8355710;
	y = 0;
	while (y < g->w.line_start)
		ft_putpixel(g, x, y++, 0x7ec0ee);
	while (y <= g->w.line_end)
		ft_putpixel(g, x, y++, clr);
	while (y < IMG_HIGHT)
		ft_putpixel(g, x, y++, 0x52361b);
	ft_play_win_sound(w);
}
