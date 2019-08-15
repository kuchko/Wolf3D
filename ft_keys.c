/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:20:42 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:20:44 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_rotate(t_wolf *w, double angle)
{
	double pre_dir_x;
	double pre_plane_x;

	pre_dir_x = w->dir_x;
	w->dir_x = w->dir_x * cos(angle) - w->dir_y * sin(angle);
	w->dir_y = pre_dir_x * sin(angle) + w->dir_y * cos(angle);
	pre_plane_x = w->plane_x;
	w->plane_x = w->plane_x * cos(angle) - w->plane_y * sin(angle);
	w->plane_y = pre_plane_x * sin(angle) + w->plane_y * cos(angle);
}

void	ft_move_all_sides(t_global *g)
{
	double	dir_forward;
	double	dir_right;
	double	dir_move_x;
	double dir_move_y;

	dir_forward = g->k.move_forward - g->k.move_back;
	dir_right = g->k.strafe_right - g->k.strafe_left;
	g->w.dir_x_sign = g->w.dir_x > 0 ? 1.0 : -1.0;
	g->w.dir_y_sign = g->w.dir_y > 0 ? 1.0 : -1.0;
	dir_move_x = (dir_forward * g->w.dir_x + dir_right * g->w.dir_y);
	dir_move_y = (dir_forward * g->w.dir_y - dir_right * g->w.dir_x);
	if (g->w.map[(int)(g->w.pos_x + dir_move_x * g->w.move_spd +
	(dir_move_x > 0 ? 1.0 : -1.0) * g->w.collision)][(int)g->w.pos_y] == 0)
		g->w.pos_x += dir_move_x * g->w.move_spd;
	if(g->w.map[(int)g->w.pos_x][(int)(g->w.pos_y + dir_move_y *
	g->w.move_spd + (dir_move_y > 0 ? 1.0 : -1.0) * g->w.collision)] == 0)
		g->w.pos_y += dir_move_y * g->w.move_spd;
}

void	ft_move_strate(t_global *g, double dir_forward)
{
	g->w.dir_x_sign = g->w.dir_x > 0 ? 1.0 : -1.0;
	g->w.dir_y_sign = g->w.dir_y > 0 ? 1.0 : -1.0;

	if (g->w.map[(int)(g->w.pos_x + dir_forward * g->w.dir_x_sign *
								g->w.collision)][(int)g->w.pos_y] == 0)
		g->w.pos_x += dir_forward * g->w.dir_x * g->w.move_spd;
	if(g->w.map[(int)g->w.pos_x][(int)(g->w.pos_y + dir_forward *
								g->w.dir_y_sign * g->w.collision)] == 0)
		g->w.pos_y += dir_forward * g->w.dir_y * g->w.move_spd;
}

void	ft_move_sides(t_global *g, double dir_right)
{
	g->w.dir_x_sign = g->w.dir_x > 0 ? 1.0 : -1.0;
	g->w.dir_y_sign = g->w.dir_y > 0 ? 1.0 : -1.0;
	if (g->w.map[(int)(g->w.pos_x + dir_right * g->w.dir_y_sign *
								g->w.collision )][(int)g->w.pos_y] == 0)
		g->w.pos_x += dir_right * g->w.dir_y * g->w.move_spd;
	if (g->w.map[(int)g->w.pos_x][(int)(g->w.pos_y - dir_right *
								g->w.dir_x_sign * g->w.collision)] == 0)
		g->w.pos_y -= dir_right * g->w.dir_x * g->w.move_spd;
}

int			ft_keys_press(int key, t_global *g)
{
	if (key == ESC)
		g->k.esc = 1;
	if (key == STRAFE_LEFT)
		g->k.strafe_left = 1;
	else if (key == STRAFE_RIGHT)
		g->k.strafe_right = 1;
	if (key == MOVE_UP || key == MOVE_W)
		g->k.move_forward = 1;
	else if (key == MOVE_DOWN || key == MOVE_S)
		g->k.move_back = 1;
	if (key == ROT_LEFT)
		g->k.rot_left = 1;
	else if (key == ROT_RIGHT)
		g->k.rot_right = 1;
	if (key > 17 && key < 21)
		g->w.tex_mode = key - 17;
	if (key == RELOAD)
		g->k.enter = 1;
	if (key == SHIFT)
		g->k.shift = 1;
	return (0);
}

int			ft_keys_unpress(int key, t_global *g)
{
	if (key == ESC)
		g->k.esc = 0;
	if (key == STRAFE_LEFT)
		g->k.strafe_left = 0;
	else if (key == STRAFE_RIGHT)
		g->k.strafe_right = 0;
	if (key == MOVE_UP || key == MOVE_W)
		g->k.move_forward = 0;
	else if (key == MOVE_DOWN || key == MOVE_S)
		g->k.move_back = 0;
	if (key == ROT_LEFT)
		g->k.rot_left = 0;
	else if (key == ROT_RIGHT)
		g->k.rot_right = 0;
	if (key == SPACE)
		g->k.space = 0;
	if (key == RELOAD)
		g->k.enter = 0;
	if (key == SHIFT)
		g->k.shift = 0;
	return (0);
}

int			ft_keys(t_keys *k, t_global *g)
{
	if (k->esc)
	{
		system("leaks wolf3d > leaks");
		exit(0);
	}
	if (k->strafe_left || k->strafe_right || k->move_forward || k->move_back)
		ft_move_all_sides(g);
	if (k->rot_left)
		ft_rotate(&g->w, g->w.rot_spd);
	else if (k->rot_right)
		ft_rotate(&g->w, -g->w.rot_spd);
	if (k->enter)
		wolf_init(g);
	g->w.move_spd = g->w.frame_tme * (k->shift ? 2.0 : 4.0);
	return (0);
}
