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
	draw_wolf3d(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	ft_bzero(g->adr, sizeof(g->adr));
	return (0);
}



int worldMap[MAP_WIDTH][MAP_HIGHT]=
{
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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void	draw_wolf3d(void *g)
{
	double pos_x = 22, pos_y = 12;  //x and y start position
	double dir_x = -1, dir_y = 0; //initial direction vector
	double plane_x = 0, plane_y = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

while(!done())
	{
		for(int x = 0; x < IMG_WIDTH; x++)
		{
			//calculate ray position and direction
			double camera_x = 2 * x / (double)IMG_WIDTH - 1; //x-coordinate in camera space  // [-1, 1] is apmlifyer for vector plane
			double ray_dir_x = dir_x + plane_x * camera_x;
			double ray_dir_y = dir_y + plane_y * camera_x;
			//which box of the map we're in
			int map_x = (int)pos_x;
			int map_y = (int)pos_y;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			 //length of ray from one x or y-side to next x or y-side
			double deltaDistX = abs(1 / ray_dir_x);
			double deltaDistY = abs(1 / ray_dir_y);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (ray_dir_x < 0)
			{
				stepX = -1;
				sideDistX = (pos_x - map_x) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (map_x + 1.0 - pos_x) * deltaDistX;
			}
			if (ray_dir_y < 0)
			{
				stepY = -1;
				sideDistY = (pos_y - map_y) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (map_y + 1.0 - pos_y) * deltaDistY;
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					map_x += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					map_y += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[map_x][map_y] > 0) hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (map_x - pos_x + (1 - stepX) / 2) / ray_dir_x;
			else 	 	 	 	 	 perpWallDist = (map_y - pos_y + (1 - stepY) / 2) / ray_dir_y;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(h / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if(drawEnd >= h)drawEnd = h - 1;

			//choose wall color
			ColorRGB color;
			switch(worldMap[map_x][map_y])
			{
				case 1: 	color = RGB_Red; 	break; //red
				case 2: 	color = RGB_Green; 	break; //green
				case 3: 	color = RGB_Blue; 	 break; //blue
				case 4: 	color = RGB_White; 	break; //white
				default: color = RGB_Yellow; break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1) {color = color / 2;}

			//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color);
		}


		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime); //FPS counter
		redraw();
		cls();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		readKeys();
		//move forward if no wall in front of you
		if (keyDown(SDLK_UP))
		{
			if(worldMap[int(pos_x + dir_x * moveSpeed)][int(pos_y)] == false) pos_x += dir_x * moveSpeed;
			if(worldMap[int(pos_x)][int(pos_y + dir_y * moveSpeed)] == false) pos_y += dir_y * moveSpeed;
		}
		//move backwards if no wall behind you
		if (keyDown(SDLK_DOWN))
		{
			if(worldMap[int(pos_x - dir_x * moveSpeed)][int(pos_y)] == false) pos_x -= dir_x * moveSpeed;
			if(worldMap[int(pos_x)][int(pos_y - dir_y * moveSpeed)] == false) pos_y -= dir_y * moveSpeed;
		}
		//rotate to the right
		if (keyDown(SDLK_RIGHT))
		{
			//both camera direction and camera plane must be rotated
			double olddir_x = dir_x;
			dir_x = dir_x * cos(-rotSpeed) - dir_y * sin(-rotSpeed);
			dir_y = olddir_x * sin(-rotSpeed) + dir_y * cos(-rotSpeed);
			double oldPlane_x = plane_x;
			plane_x = plane_x * cos(-rotSpeed) - plane_y * sin(-rotSpeed);
			plane_y = oldPlane_x * sin(-rotSpeed) + plane_y * cos(-rotSpeed);
		}
		//rotate to the left
		if (keyDown(SDLK_LEFT))
		{
			//both camera direction and camera plane must be rotated
			double olddir_x = dir_x;
			dir_x = dir_x * cos(rotSpeed) - dir_y * sin(rotSpeed);
			dir_y = olddir_x * sin(rotSpeed) + dir_y * cos(rotSpeed);
			double oldPlane_x = plane_x;
			plane_x = plane_x * cos(rotSpeed) - plane_y * sin(rotSpeed);
			plane_y = oldPlane_x * sin(rotSpeed) + plane_y * cos(rotSpeed);
		}
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
	g->mlx_ptr = mlx_init();
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIDTH, HIGHT, "Fractol");
	g->img_ptr = mlx_new_image(g->mlx_ptr, IMG_WIDTH, IMG_HIGHT);
	g->adr = mlx_get_data_addr(g->img_ptr, &g->bpp, &g->size_line, &g->endian);
	// ft_draw_menu(g);

	mlx_hook(g->win_ptr, 17, 0, ft_x, g);
	// mlx_hook(g->win_ptr, 2, 0, ft_keys, g);
	// mlx_hook(g->win_ptr, 4, 0, ft_mouse_press, g);
	// mlx_hook(g->win_ptr, 5, 0, ft_mouse_release, g);
	// mlx_hook(g->win_ptr, 6, 0, ft_mouse_move, g);
	mlx_loop(g->mlx_ptr);
	return (0);
}
