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
	w->tex_mlx_img[0] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/wood.xpm", &size, &size);
	w->tex_mlx_img[1] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/greystone_1.xpm", &size, &size);
	w->tex_mlx_img[2] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/redbrick.xpm", &size, &size);
	w->tex_mlx_img[3] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/eagle.xpm", &size, &size);
	w->tex_mlx_img[4] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_back.xpm", &size, &size);
	w->tex_mlx_img[5] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_marin.xpm", &size, &size);
	w->tex_mlx_img[6] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_red.xpm", &size, &size);
	w->tex_mlx_img[7] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_1.xpm", &size, &size);
	w->tex_mlx_img[8] = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_i.xpm", &size, &size);
	w->textures[0] = (int*)mlx_get_data_addr(w->tex_mlx_img[0],	&g->bpp, &g->size_line, &g->endian);
	w->textures[1] = (int*)mlx_get_data_addr(w->tex_mlx_img[1],	&g->bpp, &g->size_line, &g->endian);
	w->textures[2] = (int*)mlx_get_data_addr(w->tex_mlx_img[2],	&g->bpp, &g->size_line, &g->endian);
	w->textures[3] = (int*)mlx_get_data_addr(w->tex_mlx_img[3],	&g->bpp, &g->size_line, &g->endian);
	w->textures[4] = (int*)mlx_get_data_addr(w->tex_mlx_img[4],	&g->bpp, &g->size_line, &g->endian);
	w->textures[5] = (int*)mlx_get_data_addr(w->tex_mlx_img[5],	&g->bpp, &g->size_line, &g->endian);
	w->textures[6] = (int*)mlx_get_data_addr(w->tex_mlx_img[6],	&g->bpp, &g->size_line, &g->endian);
	w->textures[7] = (int*)mlx_get_data_addr(w->tex_mlx_img[7],	&g->bpp, &g->size_line, &g->endian);
	w->textures[8] = (int*)mlx_get_data_addr(w->tex_mlx_img[8],	&g->bpp, &g->size_line, &g->endian);

	// int i;

	// i = -1;
	// while(++i < 9)
	// 	g->w.tex[i].mlx = mlx_init();

	// size = TEX_HIGHT;
	// w->tex[0].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/eagle.xpm", &size, &size);
	// w->tex[1].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/greystone_1.xpm", &size, &size);
	// w->tex[2].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/redbrick.xpm", &size, &size);
	// w->tex[3].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_1.xpm", &size, &size);
	// w->tex[4].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_back.xpm", &size, &size);
	// w->tex[5].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_i.xpm", &size, &size);
	// w->tex[6].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_marin.xpm", &size, &size);
	// w->tex[7].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/unit_red.xpm", &size, &size);
	// w->tex[8].img = mlx_xpm_file_to_image(g->mlx_ptr, "xpm/wood.xpm", &size, &size);
	// w->tex[0].adr = (int*)mlx_get_data_addr(w->tex[0].img, &w->tex[0].bpp, &w->tex[0].size_line, &w->tex[0].endian);
	// w->tex[1].adr = (int*)mlx_get_data_addr(w->tex[1].img, &w->tex[1].bpp, &w->tex[1].size_line, &w->tex[1].endian);
	// w->tex[2].adr = (int*)mlx_get_data_addr(w->tex[2].img, &w->tex[2].bpp, &w->tex[2].size_line, &w->tex[2].endian);
	// w->tex[3].adr = (int*)mlx_get_data_addr(w->tex[3].img, &w->tex[3].bpp, &w->tex[3].size_line, &w->tex[3].endian);
	// w->tex[4].adr = (int*)mlx_get_data_addr(w->tex[4].img, &w->tex[4].bpp, &w->tex[4].size_line, &w->tex[4].endian);
	// w->tex[5].adr = (int*)mlx_get_data_addr(w->tex[5].img, &w->tex[5].bpp, &w->tex[5].size_line, &w->tex[5].endian);
	// w->tex[6].adr = (int*)mlx_get_data_addr(w->tex[6].img, &w->tex[6].bpp, &w->tex[6].size_line, &w->tex[6].endian);
	// w->tex[7].adr = (int*)mlx_get_data_addr(w->tex[7].img, &w->tex[7].bpp, &w->tex[7].size_line, &w->tex[7].endian);
	// w->tex[8].adr = (int*)mlx_get_data_addr(w->tex[8].img, &w->tex[8].bpp, &w->tex[8].size_line, &w->tex[8].endian);
}

void		globals_and_wolf_init(t_global *g)
{
	g->mlx_ptr = mlx_init();
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIDTH, HIGHT, "Wolf3D");
	g->img_ptr = mlx_new_image(g->mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	g->adr = mlx_get_data_addr(g->img_ptr, &g->bpp, &g->size_line, &g->endian);
	ft_bzero(&g->w, sizeof(g->w));
	ft_bzero(&g->k, sizeof(g->k));
	g->w.pos_x = 11;  //22
	g->w.pos_y = 18;  //12 //x and y start position
	g->w.dir_x = -1;
	g->w.dir_y = 0; //initial direction vector
	g->w.plane_x = 0;
	g->w.plane_y = 0.66; //the 2d raycaster version of camera plane
	g->w.ampl_wall_high = 0;
	g->w.frame_time = 0.02;
	g->w.move_speed = g->w.frame_time * 6.0; //the constant value is in squares/second
	g->w.rot_speed = g->w.frame_time * 3.0; //the constant value is in radians/second

	g->w.friction_speed = 0.0;
	ft_textures_init(g, &g->w);
	ft_printf("globals_and_wolf_init\n");

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
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,9,0,8,0,7,0,6,0,5,0,4,0,3,0,2,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,3,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

int			main(void)
{
	t_global	g;



	globals_and_wolf_init(&g);
	ft_draw(&g);
	system("leaks wolf3d > leaks");
	return (0);
}




// void		ft_textures_init(t_wolf *w)
// {
// 	int x;
// 	int y;

// 	// u_int32_t buff[IMG_HIGHT][IMG_WIDTH]; // y-coordinate first because it works per scanline
// 	// std::vector texture[8];
// 	// for(int i = 0; i < 8; i++) texture[i].resize(texWidth * TEX_HIGHT);
// 	w->textures = (int**)malloc(sizeof(int*) * 8);
// 	x = -1;
// 	while(++x < 8)
// 	{
// 		w->textures[x] = (int*)ft_memalloc(sizeof(int) * IMG_HIGHT * IMG_WIDTH);
// 	}
// 	  //generate some textures
// 	// for(int x = 0; x < texWidth; x++)
// 	w->hit = 0;
// 	x = -1;
// 	while(++x < TEX_WIDTH)
// 	{
// 		y = -1;
// 		while (++y < TEX_HIGHT)
// 		{
// 			// x = y;
// 			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HIGHT);
// 			// int xcolor = x * 256 / TEX_WIDTH;
// 			int ycolor = y * 256 / TEX_HIGHT;
// 			int xycolor = y * 128 / TEX_HIGHT + x * 128 / TEX_WIDTH;

// 			w->textures[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red w->textures with black cross
// 			w->textures[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
// 			w->textures[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
// 			w->textures[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
// 			w->textures[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
// 			w->textures[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
// 			w->textures[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
// 			w->textures[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
// 		}
// 	}
// }
