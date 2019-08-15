/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:20:00 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:20:03 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_x(void *p)
{
	(void)p;
	system("leaks fractol > leaks");
	exit(0);
	return (0);
}

int		ft_re_draw(t_global *g)
{
	// ft_printf("ft_re_draw\n");
	// ft_threads(g);
	// ft_bzero(g->adr, sizeof(g->adr));
	// mlx_clear_window(g->mlx_ptr, g->win_ptr);
	mlx_destroy_image(g->mlx_ptr, g->img_ptr);
	g->img_ptr = mlx_new_image(g->mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	ft_keys(&g->k, g);
	draw_wolf3d(g, &g->w);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	return (0);
}

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

void ft_dda_hit(t_wolf *w)
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
}

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
	w->tex_x = (int) (w->wall_x * (double)(TEX_WIDTH));
	if (w->side == 0 && w->ray_dir_x > 0)
		w->tex_x = TEX_WIDTH - w->tex_x - 1;
	if (w->side == 1 && w->ray_dir_y < 0)
		w->tex_x = TEX_WIDTH - w->tex_x - 1;
}

void ft_draw_sky_and_boxes(t_global *g, t_wolf *w, int x)
{
	int y;
	int clr;
	int sky_x;
	int sky_y;

	y = 0;
	while (y < w->line_start)
	{
		sky_x = (int) ((atan2(w->ray_dir_y, w->ray_dir_x) + M_PI)
			/ M_PI / 2.0 * (double)SKY_TEX_WIDTH);
		sky_y = (y * (double) SKY_TEX_HIGHT) / IMG_HIGHT;
		clr = w->textures[9][SKY_TEX_WIDTH * sky_y + sky_x];
		ft_putpixel(g, x, y++, clr);
	}
	while(y < w->line_end)
	{
		sky_x = y * 256 - IMG_HIGHT * 128 + w->line_height * 128;
		w->tex_y = ((sky_x * TEX_HIGHT) / w->line_height) / 256;
		clr = w->textures[w->text_num][TEX_HIGHT * w->tex_y + w->tex_x];
		if (w->side == 1)
			clr = (clr >> 1) & 8355711;
		ft_putpixel(g, x, y++, clr);
	}
}

void ft_cilling_prepare(t_wolf *w)
{
	if(w->side == 0 && w->ray_dir_x > 0)
	{
		w->flr_x_wall = w->map_x;
		w->flr_y_wall = w->map_y + w->wall_x;
	}
	else if(w->side == 0 && w->ray_dir_x < 0)
	{
		w->flr_x_wall = w->map_x + 1.0;
		w->flr_y_wall = w->map_y + w->wall_x;
	}
	else if(w->side == 1 && w->ray_dir_y > 0)
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
	int	y;
	int	c;
	int	flr_tex_x;
	int	flr_tex_y;
	double weight;

	w->dist_wall = w->p_wall_dst;
	w->dist_player = 0.0;
	if (w->line_end < 0)
		w->line_end = IMG_HIGHT;
	y = w->line_end;
	while(y < IMG_HIGHT)
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

void	draw_wolf3d(t_global *g, t_wolf *w)
{
	int x;

	// ft_printf("draw_wolf3d\n");
	x = -1;
	while(++x < IMG_WIDTH)
	{
		ft_ray_and_side_distance_calc(x, w);
		ft_dda_hit(w);
		if (w->tex_mode == 3)
			ft_colorized_environment(g, w, x);
		else
		{
			ft_texture_prepare(w);
			ft_draw_sky_and_boxes(g, w, x);
			ft_cilling_prepare(w);
			ft_draw_cilling(g, w, x);
		}
	}
}

int			ft_draw(t_global *g)
{
	ft_printf("ft_draw\n");

	ft_re_draw(g);

	mlx_hook(g->win_ptr, 17, 0, ft_x, g);
	// mlx_hook(g->win_ptr, 2, 0, ft_keys, g);
	mlx_hook(g->win_ptr, 2, 5, ft_keys_press, g);
	mlx_hook(g->win_ptr, 3, 5, ft_keys_unpress, g);

	mlx_hook(g->win_ptr, 4, 0, ft_mouse_press, g);
	// mlx_hook(g->win_ptr, 5, 0, ft_mouse_release, g);
	// mlx_hook(g->win_ptr, 6, 0, ft_mouse_move, g);
	// mlx_expose_hook (g->win_ptr, ft_re_draw, g);
	mlx_loop_hook(g->mlx_ptr, ft_re_draw, (void*)g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
