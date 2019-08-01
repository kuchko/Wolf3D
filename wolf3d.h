
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:18:56 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:19:05 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "ft_printf.h"
# include "libft.h"
# include <mlx.h>
# include <pthread.h>
# include <math.h>

# define WIDTH 1600
# define HIGHT 1000

# define IMG_WIDTH 800
# define IMG_HIGHT 500
# define MAP_WIDTH 24
# define MAP_HIGHT 24


# define TEXT_OFFSET 550

# define ESC 53
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define CENTER_ZOOM_IN 24
# define CENTER_ZOOM_OUT 27
# define ITER_PLUS 69
# define ITER_MINUS 78
# define MOVE_UP 126
# define MOVE_DOWN 125
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define COLOR_PLUS 30
# define COLOR_MINUS 33
# define ALPHA_PLUS 47
# define ALPHA_MINUS 43
# define RELOAD 36
# define THREADS 8

extern	int world_map[MAP_WIDTH][MAP_HIGHT];
//  = {
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};


typedef struct	s_wolf
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	//ray
	double camera_x; //x-coordinate in camera space  // [-1, 1] is apmlifyer for vector plane
	double ray_dir_x;
	double ray_dir_y;
	//which box of the map we're in
	int map_x;
	int map_y;
	//length of ray from current position to next x or y-side
	double side_dist_x;
	double side_dist_y;
	//length of ray from one x or y-side to next x or y-side // from pythagor
	double delt_dist_x;
	double delt_dist_y;
	double p_wall_dist;
	//what direction to step in x or y-direction (either +1 or -1)
	int step_x;
	int step_y;
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	int line_height;
	int line_start;
	int line_end;

	double frame_time;
	double move_speed; //the constant value is in squares/second
	double rot_speed;



}				t_wolf;

typedef struct	s_global
{
	void		*mlx_ptr;
	void		*img_ptr;
	void		*win_ptr;
	char		*adr;
	int			bpp;
	int			size_line;
	int			endian;

	t_wolf		w;


	pthread_t	threads[THREADS];
	int			xstart;
	int			xend;
	int			ystart;
	int			yend;
}				t_global;





void		globals_and_wolf_init(t_global *g);

void			ft_draw_menu(t_global *g);

int				ft_draw(t_global *g, t_wolf *w);
// void			draw_fractol(t_global *g);


void			ft_putpixel(t_global *f, int x, int y, int color);
int				change_color_rgb(int color, int s_x, int s_y, int alfa_step);
void			ft_print_color(int color);
void	ft_put_v_line(t_global *g, int x, int color);

int				ft_keys(int key, t_global *g);

int				ft_mouse_press(int key, int x, int y, t_global *g);
int				ft_mouse_release(int key, int x, int y, t_global *g);
int				ft_mouse_move(int x, int y, t_global *g);

void			ft_threads(t_global *g);
int				ft_re_draw(t_global *g);

void			draw_wolf3d(t_global *g, t_wolf *w);

#endif
