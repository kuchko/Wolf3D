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
	// ft_threads(g);
	draw_wolf3d(g, &g->w);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	ft_bzero(g->adr, sizeof(g->adr));
	return (0);
}



void	draw_wolf3d(t_global *g, t_wolf *w)
{
	int x;

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
			//Check if ray has hit a wall
			if (world_map[w->map_x][w->map_y] > 0) w->hit = 1;
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

		//choose wall color
		int color;
		switch(world_map[w->map_x][w->map_y])
		{
			case 1:
				color = 0xFF0000;
				break; //red
			case 2:
				color = 0x00FF00;
				break; //green
			case 3:
				color = 0x0000FF;
				break; //blue
			case 4:
				color = 0xFFFFFF;
				break; //white
			default:
				color = 0xFFFF00;
				break; //yellow
		}

		//give x and y sides different brightness
		if (w->side == 1)
			color = color / 2;
		//draw the pixels of the stripe as a vertical line
		// verLine(x, line_start, line_end, color);
		ft_put_v_line(g, x, color);
	}


		//timing for input and FPS counter
		// oldTime = time;
		// time = getTicks();
		// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		// print(1.0 / frameTime); //FPS counter
		// redraw();
		// cls();

		//speed modifiers
		// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

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

int			ft_draw(t_global *g, t_wolf *w)
{

	// ft_draw_menu(g);
	draw_wolf3d(g, w);
	mlx_hook(g->win_ptr, 17, 0, ft_x, g);
	// mlx_hook(g->win_ptr, 2, 0, ft_keys, g);
	// mlx_hook(g->win_ptr, 4, 0, ft_mouse_press, g);
	// mlx_hook(g->win_ptr, 5, 0, ft_mouse_release, g);
	// mlx_hook(g->win_ptr, 6, 0, ft_mouse_move, g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
