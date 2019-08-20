/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:42:48 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:42:50 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_set_textures(t_global *g, t_wolf *w)
{
	int	*b;
	int	*sl;
	int	*e;

	b = &g->bpp;
	sl = &g->size_line;
	e = &g->endian;
	w->textures[0] = (int*)mlx_get_data_addr(w->tex_mlx_img[0], b, sl, e);
	w->textures[1] = (int*)mlx_get_data_addr(w->tex_mlx_img[1], b, sl, e);
	w->textures[2] = (int*)mlx_get_data_addr(w->tex_mlx_img[2], b, sl, e);
	w->textures[3] = (int*)mlx_get_data_addr(w->tex_mlx_img[3], b, sl, e);
	w->textures[4] = (int*)mlx_get_data_addr(w->tex_mlx_img[4], b, sl, e);
	w->textures[5] = (int*)mlx_get_data_addr(w->tex_mlx_img[5], b, sl, e);
	w->textures[6] = (int*)mlx_get_data_addr(w->tex_mlx_img[6], b, sl, e);
	w->textures[7] = (int*)mlx_get_data_addr(w->tex_mlx_img[7], b, sl, e);
	w->textures[8] = (int*)mlx_get_data_addr(w->tex_mlx_img[8], b, sl, e);
	w->textures[9] = (int*)mlx_get_data_addr(w->tex_mlx_img[9], b, sl, e);
}

static void	ft_textures_init(t_global *g, t_wolf *w)
{
	int s;
	int sky_hight;
	int sky_width;

	s = TEX_HIGHT;
	sky_hight = SKY_TEX_HIGHT;
	sky_width = SKY_TEX_WIDTH;
	if ((w->tex_mlx_img[0] = MTI(g->mlx_ptr, "xpm/wood.xpm", &s, &s))
	&& (w->tex_mlx_img[1] = MTI(g->mlx_ptr, "xpm/greystone_1.xpm", &s, &s))
	&& (w->tex_mlx_img[2] = MTI(g->mlx_ptr, "xpm/redbrick.xpm", &s, &s))
	&& (w->tex_mlx_img[3] = MTI(g->mlx_ptr, "xpm/eagle.xpm", &s, &s))
	&& (w->tex_mlx_img[4] = MTI(g->mlx_ptr, "xpm/unit_back.xpm", &s, &s))
	&& (w->tex_mlx_img[5] = MTI(g->mlx_ptr, "xpm/unit_marin.xpm", &s, &s))
	&& (w->tex_mlx_img[6] = MTI(g->mlx_ptr, "xpm/unit_red.xpm", &s, &s))
	&& (w->tex_mlx_img[7] = MTI(g->mlx_ptr, "xpm/unit_1.xpm", &s, &s))
	&& (w->tex_mlx_img[8] = MTI(g->mlx_ptr, "xpm/unit_i.xpm", &s, &s))
	&& (w->tex_mlx_img[9] = MTI(g->mlx_ptr, "xpm/sky.xpm",
	&sky_width, &sky_hight)))
		ft_set_textures(g, w);
	else
		ft_error("Textures files failed\n");
}

void		wolf_init(t_global *g)
{
	g->w.pos_x = g->w.pos_start_x;
	g->w.pos_y = g->w.pos_start_y;
	g->w.dir_x = -1;
	g->w.dir_y = 0;
	g->w.plane_x = 0;
	g->w.plane_y = 0.66;
	g->w.frame_tme = 0.02;
	g->w.move_spd = g->w.frame_tme * 4.0;
	g->w.rot_spd = g->w.frame_tme * 2.0;
	g->w.tex_mode = 1;
	g->w.collision = 0.1;
	g->w.win_play = 0;
	ft_rotate(&g->w, M_PI + M_PI_4 + 0.001);
}

int			main(int argc, char **argv)
{
	t_global	g;
	t_list		*start;

	ft_bzero(&g.w, sizeof(g.w));
	ft_bzero(&g.k, sizeof(g.k));
	wolf_init(&g);
	ft_read(&g, &start, argc, argv);
	g.mlx_ptr = mlx_init();
	g.win_ptr = mlx_new_window(g.mlx_ptr, WIDTH, HIGHT, "Wolf3D");
	g.img_ptr = mlx_new_image(g.mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	g.adr = mlx_get_data_addr(g.img_ptr, &g.bpp, &g.size_line, &g.endian);
	ft_textures_init(&g, &g.w);
	system("afplay ./xpm/woopie.mp3&");
	ft_draw(&g);
	system("leaks wolf3d > leaks");
	return (0);
}
