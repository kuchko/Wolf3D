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

void	ft_threads(t_global *g)
{
	t_global	glbl[THREADS];
	int			i;

	i = -1;
	while (++i < THREADS)
	{
		glbl[i] = *g;
		glbl[i].xstart = 0;
		glbl[i].xend = IMG_WIDTH;
		glbl[i].ystart = IMG_HIGHT / THREADS * i;
		glbl[i].yend = IMG_HIGHT / THREADS * (i + 1);
		pthread_create(&g->threads[i], NULL,
		(void *)draw_wolf3d, (void *)&glbl[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(g->threads[i], NULL);
}

int		ft_re_draw(t_global *g)
{
	ft_printf("ft_re_draw\n");
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



void	draw_wolf3d(t_global *g, t_wolf *w)
{
	int x;

	ft_printf("draw_wolf3d\n");
	x = -1;
	while(++x < IMG_WIDTH)
	{
		//calculate ray position and direction
		w->camera_x = 2 * x / (double)IMG_WIDTH - 1; //x-coordinate in camera space  // [-1, 1] is apmlifyer for vector plane
		w->ray_dir_x = w->dir_x + w->plane_x * w->camera_x;
		w->ray_dir_y = w->dir_y + w->plane_y * w->camera_x;
		//which box of the map we're in
		w->map_x = (int)w->pos_x;
		w->map_y = (int)w->pos_y;
			//length of ray from one x or y-side to next x or y-side // from pythagor
		w->delt_dist_x = fabs(1 / w->ray_dir_x);
		w->delt_dist_y = fabs(1 / w->ray_dir_y);
		w->hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if (w->ray_dir_x < 0)
		{
			w->step_x = -1;
			w->side_dist_x = (w->pos_x - w->map_x) * w->delt_dist_x;
		}
		else
		{
			w->step_x = 1;
			w->side_dist_x = (w->map_x + 1.0 - w->pos_x) * w->delt_dist_x;
		}
		if (w->ray_dir_y < 0)
		{
			w->step_y = -1;
			w->side_dist_y = (w->pos_y - w->map_y) * w->delt_dist_y;
		}
		else
		{
			w->step_y = 1;
			w->side_dist_y = (w->map_y + 1.0 - w->pos_y) * w->delt_dist_y;
		}
		//perform DDA
		while (w->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (w->side_dist_x < w->side_dist_y)
			{
				w->side_dist_x += w->delt_dist_x;
				w->map_x += w->step_x;
				w->side = 0;
			}
			else
			{
				w->side_dist_y += w->delt_dist_y;
				w->map_y += w->step_y;
				w->side = 1;
			}
			// ft_printf("draw_wolf3d - befor: [%d, %d] = %d\n", w->map_x, w->map_y,world_map[w->map_x][w->map_y]);

			//Check if ray has hit a wall
			if (world_map[w->map_x][w->map_y] > 0)
				w->hit = 1;
			// ft_printf("draw_wolf3d - after: [%d, %d] = %d\n", w->map_x, w->map_y,world_map[w->map_x][w->map_y]);
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (w->side == 0)
			w->p_wall_dist = (w->map_x - w->pos_x + (1 - w->step_x) / 2) / w->ray_dir_x;
		else
			w->p_wall_dist = (w->map_y - w->pos_y + (1 - w->step_y) / 2) / w->ray_dir_y;

		//Calculate height of line to draw on screen
		w->line_height = (int)(IMG_HIGHT / w->p_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		w->line_start = -w->line_height / 2 + IMG_HIGHT / 2;
		if (w->line_start < 0)
			w->line_start = 0;
		w->line_end = w->line_height / 2 + IMG_HIGHT / 2;
		if (w->line_end >= IMG_HIGHT)
			w->line_end = IMG_HIGHT - 1;
		// ft_printf("color check\n");

////////////////////// FILL WALLS BY COLORS ////////////////////
		//choose wall color
		// int color;
		// switch(world_map[w->map_x][w->map_y])
		// {
		// 	case 1:
		// 		color = 0xFF0000;
		// 		break; //red
		// 	case 2:
		// 		color = 0x00FF00;
		// 		break; //green
		// 	case 3:
		// 		color = 0x0000FF;
		// 		break; //blue
		// 	case 4:
		// 		color = 0xFFFFFF;
		// 		break; //white
		// 	default:
		// 		color = 0xFFFF00;
		// 		break; //yellow
		// }
		// ft_printf("color = %x\n", color);
		//give x and y sides different brightness
		// if (w->side == 1)
		// 	color = color / 2;
		//draw the pixels of the stripe as a vertical line
		// ft_put_v_line(g, x, color);
//////////////////////////////////////////////////////////////////
		// ft_put_v_line(g, 10, 0xFF00FF);

		// ft_printf("debug texturing\n");

		//texturing calculations
		w->text_num = world_map[w->map_x][w->map_y] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of w->wall_x
		// double w->wall_x; //where exactly the wall was hit
		if (w->side == 0)
			w->wall_x = w->pos_y + w->p_wall_dist * w->ray_dir_y;
		else
			w->wall_x = w->pos_x + w->p_wall_dist * w->ray_dir_x;
		w->wall_x -= floor((w->wall_x));


		///choose textures for sides

		if (w->text_num < 8)
		{
			if (w->side == 0)
				w->text_num = w->ray_dir_x > 0 ? 0 : 1;
			else
				w->text_num = w->ray_dir_y > 0 ? 2 : 3;
			w->text_num += w->tex_change_flag * 4;
		}

		// ft_printf("texture_number = %d\n",texture_number);

		//x coordinate on the texture
		w->tex_x = (int) (w->wall_x * (double)(TEX_WIDTH));
		if (w->side == 0 && w->ray_dir_x > 0)
			w->tex_x = TEX_WIDTH - w->tex_x - 1;
		if (w->side == 1 && w->ray_dir_y < 0)
			w->tex_x = TEX_WIDTH - w->tex_x - 1;
		// ft_printf("debug texturing2\n");
		int y;
		int d;
		int color;

		for(y = w->line_start; y < w->line_end; y++)
		{
			d = y * 256 - IMG_HIGHT * 128 + w->line_height * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			w->tex_y = ((d * TEX_HIGHT) / w->line_height) / 256;

			color = w->textures[w->text_num][TEX_HIGHT * w->tex_y + w->tex_x];
			// int color = w->textures[w->text_num][TEX_HIGHT * w->tex_y + tex_x];
			if (w->side == 1)
				color = (color >> 1) & 8355711;
			ft_putpixel(g, x, y, color);
			// if (x == 600)
			// {
			// 	ft_printf("ft_put_pixel tex = %d, {%d, %d}; ", w->text_num,  x, y);
			// 	ft_print_color(color);
			// }
		}

		/////////////////////FLOR AND CILING TEXTURING

		//FLOOR CASTING
		double flr_x_wall, flr_y_wall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(w->side == 0 && w->ray_dir_x > 0)
		{
			flr_x_wall = w->map_x;
			flr_y_wall = w->map_y + w->wall_x;
		}
		else if(w->side == 0 && w->ray_dir_x < 0)
		{
			flr_x_wall = w->map_x + 1.0;
			flr_y_wall = w->map_y + w->wall_x;
		}
		else if(w->side == 1 && w->ray_dir_y > 0)
		{
			flr_x_wall = w->map_x + w->wall_x;
			flr_y_wall = w->map_y;
		}
		else
		{
			flr_x_wall = w->map_x + w->wall_x;
			flr_y_wall = w->map_y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = w->p_wall_dist;
		distPlayer = 0.0;

		if (w->line_end < 0) w->line_end = IMG_HIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(y = w->line_end; y < IMG_HIGHT; y++)
		{
			currentDist = IMG_HIGHT / (2.0 * y - IMG_HIGHT); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * flr_x_wall + (1.0 - weight) * w->pos_x;
			double currentFloorY = weight * flr_y_wall + (1.0 - weight) * w->pos_y;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
			floorTexY = (int)(currentFloorY * TEX_HIGHT) % TEX_HIGHT;

			//floor
			// buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)

			color = (w->textures[0][TEX_WIDTH * floorTexY + floorTexX] >> 1) & 8355711;
			ft_putpixel(g, x, y, color);

		}

		//sky texturing
		for(y = 0; y < w->line_start; y++)
		{
			double atan = (atan2(w->ray_dir_y, w->ray_dir_x) + M_PI) / M_PI / 2.0;// * 180.0 / M_PI;  0 -> 2pi ; 0 -> 1
			int sky_x = (int) (atan * (double)SKY_TEX_WIDTH);
			int sky_y = (y * (double) SKY_TEX_HIGHT) / IMG_HIGHT;
			color = w->textures[9][SKY_TEX_WIDTH * sky_y + sky_x];
			ft_putpixel(g, x, y, color);
		}

		// for(y = 0; y < w->line_start; y++)
		// {
		// 	double atan = (atan2(w->ray_dir_y, w->ray_dir_x) + M_PI) / M_PI / 2.0;// * 180.0 / M_PI;  0 -> 2pi ; 0 -> 1
		// 	int sky_x = (int) (atan * (double)TEX_WIDTH);
		// 	int sky_y = (2 * y * TEX_HIGHT) / IMG_HIGHT;
		// 	color = w->textures[8][TEX_WIDTH * sky_y + sky_x];
		// 	ft_putpixel(g, x, y, color);
		// }

		//sky texturing
		// for(y = 0; y < w->line_start; y++)
		// {
		// 	double atan = (atan2(w->dir_y, w->dir_x) + M_PI) / M_PI / 2.0;// * 180.0 / M_PI;  0 -> 2pi ; 0 -> 1
		// 	int sky_x = (int)(((double)x / (double)IMG_WIDTH + 4.0 - 4.0 * atan) / 4.0 * (double)TEX_WIDTH);
		// 	int sky_y = (2 * y * TEX_HIGHT) / IMG_HIGHT;
		// 	color = w->textures[8][TEX_WIDTH * sky_y + sky_x];
		// 	ft_putpixel(g, x, y, color);
			// if (x == 600)
			// {
			// 	ft_printf("ft_put_pixel tex = %d, {%d, %d};\t %f\t", w->text_num, x, y, atan);
			// 	ft_print_color(color);
			// }
		// }


		// ft_printf("debug texturing3\n");
	}
}


// void	draw_wolf3d(void *g)
// {
// 	int	y;
// 	int	x;
// 	int	(*iterate[8])(t_global*);

// 	iterate[0] = &julia_iter;
// 	iterate[1] = &mandelbrot_iter;
// 	iterate[2] = &buffalo_iter;
// 	iterate[3] = &burningship_iter;
// 	iterate[4] = &burningstar_iter;
// 	iterate[5] = &burning5th_iter;
// 	iterate[6] = &mandelbrot_tricorn_iter;
// 	iterate[7] = &mandelbrot_4th_iter;
// 	y = g->ystart;
// 	while (y < g->yend)
// 	{
// 		x = g->xstart;
// 		while (x < g->xend)
// 		{
// 			iteration_init(g, x, y);
// 			pixel_calc_color(g, iterate[g->fractol_select - 1](g));
// 			ft_putpixel(g, x, y, g->fr.color);
// 			x++;
// 		}
// 		y++;
// 	}
// }


int			ft_draw(t_global *g)
{
	ft_printf("ft_draw\n");

	// ft_draw_menu(g);
	// draw_wolf3d(g, w);
	ft_re_draw(g);

	mlx_hook(g->win_ptr, 17, 0, ft_x, g);
	// mlx_hook(g->win_ptr, 2, 0, ft_keys, g);
	mlx_hook(g->win_ptr, 2, 5, ft_keys_press, g);
	mlx_hook(g->win_ptr, 3, 5, ft_keys_unpress, g);

	// mlx_hook(g->win_ptr, 4, 0, ft_mouse_press, g);
	// mlx_hook(g->win_ptr, 5, 0, ft_mouse_release, g);
	// mlx_hook(g->win_ptr, 6, 0, ft_mouse_move, g);
	// mlx_expose_hook (g->win_ptr, ft_re_draw, g);
	mlx_loop_hook(g->mlx_ptr, ft_re_draw, (void*)g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
