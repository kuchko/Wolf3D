/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:22:17 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:22:19 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_textures_init(t_global *g, t_wolf *w)
{
	int size;

	// w->tex_mlx_img = (void**)malloc(sizeof(void*) * 9);
	// w->textures = (int**)malloc(sizeof(int*) * 9);

	size = TEX_HIGHT;
	int sky_hight = SKY_TEX_HIGHT;
	int sky_width = SKY_TEX_WIDTH;
	w->tex_mlx_img[0] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/wood.xpm", &size, &size);
	w->tex_mlx_img[1] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/greystone_1.xpm", &size, &size);
	w->tex_mlx_img[2] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/redbrick.xpm", &size, &size);
	w->tex_mlx_img[3] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/eagle.xpm", &size, &size);
	w->tex_mlx_img[4] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_back.xpm", &size, &size);
	w->tex_mlx_img[5] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_marin.xpm", &size, &size);
	w->tex_mlx_img[6] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_red.xpm", &size, &size);
	w->tex_mlx_img[7] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_1.xpm", &size, &size);
	w->tex_mlx_img[8] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_i.xpm", &size, &size);
	w->tex_mlx_img[9] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/sky.xpm", &sky_width, &sky_hight);
	w->textures[0] = (int*)mlx_get_data_addr(w->tex_mlx_img[0],	&g->bpp, &g->size_line, &g->endian);
	w->textures[1] = (int*)mlx_get_data_addr(w->tex_mlx_img[1],	&g->bpp, &g->size_line, &g->endian);
	w->textures[2] = (int*)mlx_get_data_addr(w->tex_mlx_img[2],	&g->bpp, &g->size_line, &g->endian);
	w->textures[3] = (int*)mlx_get_data_addr(w->tex_mlx_img[3],	&g->bpp, &g->size_line, &g->endian);
	w->textures[4] = (int*)mlx_get_data_addr(w->tex_mlx_img[4],	&g->bpp, &g->size_line, &g->endian);
	w->textures[5] = (int*)mlx_get_data_addr(w->tex_mlx_img[5],	&g->bpp, &g->size_line, &g->endian);
	w->textures[6] = (int*)mlx_get_data_addr(w->tex_mlx_img[6],	&g->bpp, &g->size_line, &g->endian);
	w->textures[7] = (int*)mlx_get_data_addr(w->tex_mlx_img[7],	&g->bpp, &g->size_line, &g->endian);
	w->textures[8] = (int*)mlx_get_data_addr(w->tex_mlx_img[8],	&g->bpp, &g->size_line, &g->endian);
	w->textures[9] = (int*)mlx_get_data_addr(w->tex_mlx_img[9],	&g->bpp, &g->size_line, &g->endian);

}

void		wolf_init(t_global *g)
{

	g->w.pos_x = 11;  //22
	g->w.pos_y = 18;  //12 //x and y start position
	g->w.dir_x = -1;
	g->w.dir_y = 0; //initial direction vector
	g->w.plane_x = 0;
	g->w.plane_y = 0.66; //the 2d raycaster version of camera plane
	g->w.frame_tme = 0.02;
	g->w.move_spd = g->w.frame_tme * 4.0; //the constant value is in squares/second
	g->w.rot_spd = g->w.frame_tme * 2.0; //the constant value is in radians/second
	g->w.tex_mode = 1;
	g->w.collision = 0.1;
	ft_rotate(&g->w, 0.001);

		// double	pre_dir_x = g->w.dir_x;
		// g->w.dir_x = g->w.dir_x * cos(0.005) - g->w.dir_y * sin(0.005);
		// g->w.dir_y = pre_dir_x * sin(0.005) + g->w.dir_y * cos(0.005);
		// double	pre_plane_x = g->w.plane_x;
		// g->w.plane_x = g->w.plane_x * cos(0.005) - g->w.plane_y * sin(0.005);
		// g->w.plane_y = pre_plane_x * sin(0.005) + g->w.plane_y * cos(0.005);

	// ft_printf("globals_and_wolf_init\n");

}

// static void	ft_input_select(int argc, char **argv, t_global *g)
// {
// 	if (argc == 1)
// 	{
// 		ft_printf("usage:	wolf3d map_file\n");
// 		ft_error("map_file - is rectangualr shaped map max [100,100] sized \n");
// 	}
// }

// int			main(int argc, char **argv)


int world_map[MAP_WIDTH][MAP_HIGHT] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// int world_map[MAP_WIDTH][MAP_HIGHT] = {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,9,0,8,0,7,0,6,0,5,0,4,0,3,0,2,0,1,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };


int			main(void)
{
	t_global	g;

	g.mlx_ptr = mlx_init();
	g.win_ptr = mlx_new_window(g.mlx_ptr, WIDTH, HIGHT, "Wolf3D");
	g.img_ptr = mlx_new_image(g.mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	g.adr = mlx_get_data_addr(g.img_ptr, &g.bpp, &g.size_line, &g.endian);
	ft_bzero(&g.w, sizeof(g.w));
	ft_bzero(&g.k, sizeof(g.k));
	ft_textures_init(&g, &g.w);
	wolf_init(&g);

	ft_draw(&g);
	system("leaks wolf3d > leaks");
	return (0);
}
