
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
# define MOVE_LEFT 123
# define MOVE_RIGHT 124
# define COLOR_PLUS 30
# define COLOR_MINUS 33
# define ALPHA_PLUS 47
# define ALPHA_MINUS 43
# define RELOAD 36
# define THREADS 8

typedef struct	s_fractol
{
	double	c_re;
	double	c_im;
	double	stp_re;
	double	stp_im;
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	double	zoom;
	double	zoom_step;
	double	move_x;
	double	move_y;
	int		color;
	int		c_step_x;
	int		c_step_y;
	int		a_s;
	int		max_iterations;
	int		flag_move;
	int		flag_color_move;
	int		x_pre;
	int		y_pre;
}				t_fractol;

typedef struct	s_global
{
	void		*mlx_ptr;
	void		*img_ptr;
	void		*win_ptr;
	char		*adr;
	int			bpp;
	int			size_line;
	int			endian;
	int			fractol_select;
	t_fractol	fr;

	pthread_t	threads[THREADS];
	int			xstart;
	int			xend;
	int			ystart;
	int			yend;
}				t_global;

void			globals_init(t_global *g);

void			ft_draw_menu(t_global *g);

int				ft_draw(t_global *g);
// void			draw_fractol(t_global *g);


void			ft_putpixel(t_global *f, int x, int y, int color);
int				change_color_rgb(int color, int s_x, int s_y, int alfa_step);
void			ft_print_color(int color);

int				ft_keys(int key, t_global *g);

int				ft_mouse_press(int key, int x, int y, t_global *g);
int				ft_mouse_release(int key, int x, int y, t_global *g);
int				ft_mouse_move(int x, int y, t_global *g);

void			ft_threads(t_global *g);
int				ft_re_draw(t_global *g);

void	draw_wolf3d(void *g);

#endif
