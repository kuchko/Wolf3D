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

	// g->w.pos_x = 11.5;
	// g->w.pos_y = 18.5;
	g->w.pos_x = 0.0;
	g->w.pos_y = 0.0;
	g->w.dir_x = -1;
	g->w.dir_y = 0;
	g->w.plane_x = 0;
	g->w.plane_y = 0.66;
	g->w.frame_tme = 0.02;
	g->w.move_spd = g->w.frame_tme * 4.0;
	g->w.rot_spd = g->w.frame_tme * 2.0;
	g->w.tex_mode = 1;
	g->w.collision = 0.1;
	ft_rotate(&g->w, M_PI + M_PI_4 + 0.001);
}

// int world_map[MAP_WIDTH][MAP_HIGHT] = {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,2,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

static int	ft_valid_symbols(t_list *lst, int y_range)
{
	int	i;
	int	j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (((char*)lst->content)[j])
			if (ft_strchr("012,", ((char*)lst->content)[j++]) == NULL)
				return (0);
		lst = lst->next;
		i++;
	}
	if (i == y_range)
		return (1);
	return (0);
}

static int	ft_read_to_list(t_list **start, int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*l;
	int		i;

	i = 0;
	while (get_next_line(fd, &l) > 0 && ++i)
	{
		if (*start == NULL)
		{
			if ((*start = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst = *start;
		}
		else
		{
			if ((tmp = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst->next = tmp;
			lst = tmp;
		}
		free(l);
	}
	i > 0 ? free(l) : 0;
	return (i);
}

void		ft_read(t_global *g, t_list **start, int argc, char **argv)
{
	int		fd;

	*start = NULL;
	if (argc == 1)
		ft_error("usage:	wolf3D map_file\n");
	if (argc > 2)
		ft_error("wolf3D must have only one map_file\n");
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
		ft_error("open directory is invalid\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error("open map_file error\n");
	if ((g->w.map_size_y = ft_read_to_list(start, fd)) == 0)
		ft_error("invalid file content\n");
	close(fd);
	if (g->w.map_size_y > 100)
		ft_error("map is too big\n");
	if (ft_valid_symbols(*start, g->w.map_size_y) == 0)
		ft_error("invalid symbols in file\n");
	if (!ft_validate_map(*start, &g->w))
		ft_error("map error. coordinates might be out of range.\n");
}

void	ft_show_list(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void	ft_show_map(t_wolf *w)
{
	int	x;
	int y;

	y = -1;
	ft_printf("map[%d][%d] - position(%f,%f):\n", w->map_size_y, w->map_size_x, w->pos_y, w->pos_x);
	while (++y < w->map_size_y)
	{
		x = -1;
		while (++x < w->map_size_x)
		{
			ft_printf("%d ", w->map[y][x]);
		}
		ft_printf("\n");
	}
}


int			main(int argc, char **argv)
{
	t_global	g;
	t_list	*start;


	ft_bzero(&g.w, sizeof(g.w));
	ft_bzero(&g.k, sizeof(g.k));
	wolf_init(&g);

	ft_read(&g, &start, argc, argv);

	ft_show_list(start);
	ft_show_map(&g.w);



	g.mlx_ptr = mlx_init();
	g.win_ptr = mlx_new_window(g.mlx_ptr, WIDTH, HIGHT, "Wolf3D");
	g.img_ptr = mlx_new_image(g.mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	g.adr = mlx_get_data_addr(g.img_ptr, &g.bpp, &g.size_line, &g.endian);
	ft_textures_init(&g, &g.w);

	ft_draw(&g);
	system("leaks wolf3d > leaks");
	return (0);
}
