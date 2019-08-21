/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:39:41 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:40:55 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_play_win_sound(t_wolf *w)
{
	if (w->win_play == 0 && w->map[w->map_x][w->map_y] == 2)
	{
		w->win_play = 1;
		system("afplay ./xpm/WIN_00.mp3&");
	}
}

static int	ft_x(void *p)
{
	(void)p;
	system("leaks wolf3d > leaks");
	exit(0);
	return (0);
}

static void	draw_wolf3d(t_global *g, t_wolf *w)
{
	int x;

	x = -1;
	while (++x < IMG_WIDTH)
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

static int	ft_re_draw(t_global *g)
{
	mlx_destroy_image(g->mlx_ptr, g->img_ptr);
	g->img_ptr = mlx_new_image(g->mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	ft_keys(&g->k, g);
	draw_wolf3d(g, &g->w);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	return (0);
}

int			ft_draw(t_global *g)
{
	ft_re_draw(g);
	mlx_hook(g->win_ptr, 17, 0, ft_x, g);
	mlx_hook(g->win_ptr, 2, 5, ft_keys_press, g);
	mlx_hook(g->win_ptr, 3, 5, ft_keys_unpress, g);
	mlx_loop_hook(g->mlx_ptr, ft_re_draw, (void*)g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
