
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
# include "get_next_line.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define WIDTH 1200
# define HIGHT 800

# define IMG_WIDTH 1200
# define IMG_HIGHT 800
// # define MAP_WIDTH 24
// # define MAP_HIGHT 24
# define TEX_WIDTH 64
# define TEX_HIGHT 64
# define SKY_TEX_WIDTH 2048
# define SKY_TEX_HIGHT 512


# define TEXT_OFFSET 550

# define ESC 53
# define SHIFT 257
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define ZOOM_IN 4
# define ZOOM_OUT 5
# define CENTER_ZOOM_IN 24
# define CENTER_ZOOM_OUT 27
# define PLUS 69
# define MINUS 78
# define MOVE_UP 126
# define MOVE_DOWN 125
# define ROT_LEFT 123
# define ROT_RIGHT 124
# define MOVE_W 13
# define MOVE_S 1
# define STRAFE_LEFT 0
# define STRAFE_RIGHT 2
# define COLOR_PLUS 30
# define COLOR_MINUS 33
# define ALPHA_PLUS 47
# define ALPHA_MINUS 43
# define RELOAD 36
# define SPACE 49
# define THREADS 8

// extern	int world_map[MAP_WIDTH][MAP_HIGHT];

typedef struct	s_keys
{
	int			esc;
	int			move_forward;
	int			move_back;
	int			strafe_left;
	int			strafe_right;
	int			rot_left;
	int			rot_right;

	int			shift;
	int			ctrl;
	int			space;
	int			enter;

	int			plus;
	int			minus;

}				t_keys;


typedef struct	s_wolf
{
	int			map_size_y;
	int			map_size_x;
	int			**map;

	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		dir_x_sign;
	double		dir_y_sign;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dst_x;
	double		side_dst_y;

	double		p_wall_dst;
	double		delt_dst_x;
	double		delt_dst_y;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;

	int			line_height;
	int			line_start;
	int			line_end;

	double		frame_tme;
	double		move_spd;
	double		rot_spd;

	int			tex_mode;
	int			text_num;
	void		*tex_mlx_img[10];
	int			*textures[10];
	double		wall_x;
	int			tex_x;
	int			tex_y;

	double		flr_x_wall;
	double		flr_y_wall;
	double		dist_wall;
	double		dist_player;
	double		crnt_dist;

	double		collision;
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
	t_keys		k;
}				t_global;



int			ft_validate_map(t_list *lst, t_wolf *w);

void			globals_and_wolf_init(t_global *g);
void			wolf_init(t_global *g);

void			ft_draw_menu(t_global *g);

int				ft_draw(t_global *g);



void			ft_putpixel(t_global *f, int x, int y, int color);
int				change_color_rgb(int color, int s_x, int s_y, int alfa_step);
void			ft_print_color(int color);
void			ft_put_v_line(t_global *g, int x, int color);
void			ft_put_buff(t_global *g);

void	ft_rotate(t_wolf *w, double angle);
void	ft_move_strate(t_global *g, double dir_forward);
void	ft_move_sides(t_global *g, double dir_right);
int				ft_keys(t_keys *k, t_global *g);
// int				ft_keys(int key, t_global *g);

int				ft_keys_press(int key, t_global *g);
int				ft_keys_unpress(int key, t_global *g);

int				ft_mouse_press(int key, int x, int y, t_global *g);
int				ft_mouse_release(int key, int x, int y, t_global *g);
int				ft_mouse_move(int x, int y, t_global *g);

int				ft_re_draw(t_global *g);

void			draw_wolf3d(t_global *g, t_wolf *w);

#endif
