/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_with_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:41:17 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:41:19 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_texture_prepare(t_wolf *w)
{
	w->text_num = w->map[w->map_x][w->map_y] - 1;
	if (w->text_num == 0)
	{
		if (w->side == 0)
			w->text_num = w->ray_dir_x > 0 ? 0 : 1;
		else
			w->text_num = w->ray_dir_y > 0 ? 2 : 3;
		w->text_num += (w->tex_mode - 1) * 4;
	}
	else
		w->text_num = 8;
	if (w->side == 0)
		w->wall_x = w->pos_y + w->p_wall_dst * w->ray_dir_y;
	else
		w->wall_x = w->pos_x + w->p_wall_dst * w->ray_dir_x;
	w->wall_x -= floor((w->wall_x));
	w->tex_x = (int)(w->wall_x * (double)(TEX_WIDTH));
	if (w->side == 0 && w->ray_dir_x > 0)
		w->tex_x = TEX_WIDTH - w->tex_x - 1;
	if (w->side == 1 && w->ray_dir_y < 0)
		w->tex_x = TEX_WIDTH - w->tex_x - 1;
}

void	ft_draw_sky_and_boxes(t_global *g, t_wolf *w, int x)
{
	int y;
	int clr;
	int sky_x;
	int sky_y;

	y = 0;
	while (y < w->line_start)
	{
		sky_x = (int)((atan2(w->ray_dir_y, w->ray_dir_x) + M_PI)
			/ M_PI / 2.0 * (double)SKY_TEX_WIDTH);
		sky_y = (y * (double)SKY_TEX_HIGHT) / IMG_HIGHT;
		clr = w->textures[9][SKY_TEX_WIDTH * sky_y + sky_x];
		ft_putpixel(g, x, y++, clr);
	}
	while (y < w->line_end)
	{
		sky_x = y * 256 - IMG_HIGHT * 128 + w->line_height * 128;
		w->tex_y = ((sky_x * TEX_HIGHT) / w->line_height) / 256;
		clr = w->textures[w->text_num][TEX_HIGHT * w->tex_y + w->tex_x];
		if (w->side == 1)
			clr = (clr >> 1) & 8355711;
		ft_putpixel(g, x, y++, clr);
	}
	ft_play_win_sound(w);
}

void	ft_cilling_prepare(t_wolf *w)
{
	if (w->side == 0 && w->ray_dir_x > 0)
	{
		w->flr_x_wall = w->map_x;
		w->flr_y_wall = w->map_y + w->wall_x;
	}
	else if (w->side == 0 && w->ray_dir_x < 0)
	{
		w->flr_x_wall = w->map_x + 1.0;
		w->flr_y_wall = w->map_y + w->wall_x;
	}
	else if (w->side == 1 && w->ray_dir_y > 0)
	{
		w->flr_x_wall = w->map_x + w->wall_x;
		w->flr_y_wall = w->map_y;
	}
	else
	{
		w->flr_x_wall = w->map_x + w->wall_x;
		w->flr_y_wall = w->map_y + 1.0;
	}
}

void	ft_draw_cilling(t_global *g, t_wolf *w, int x)
{
	int		y;
	int		c;
	int		flr_tex_x;
	int		flr_tex_y;
	double	weight;

	w->dist_wall = w->p_wall_dst;
	w->dist_player = 0.0;
	if (w->line_end < 0)
		w->line_end = IMG_HIGHT;
	y = w->line_end;
	while (y < IMG_HIGHT)
	{
		w->crnt_dist = IMG_HIGHT / (2.0 * y - IMG_HIGHT);
		weight = (w->crnt_dist - w->dist_player) /
							(w->dist_wall - w->dist_player);
		flr_tex_x = (int)((weight * w->flr_x_wall + (1.0 - weight) * w->pos_x)
													* TEX_WIDTH) % TEX_WIDTH;
		flr_tex_y = (int)((weight * w->flr_y_wall + (1.0 - weight) * w->pos_y)
													* TEX_HIGHT) % TEX_HIGHT;
		c = (w->textures[0][TEX_WIDTH * flr_tex_y + flr_tex_x] >> 1) & 8355711;
		ft_putpixel(g, x, y++, c);
	}
}
