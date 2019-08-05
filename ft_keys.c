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

// static int	ft_keys_select(int key, t_global *g)
// {
// 	if (key > 17 && key < 22)
// 		g->fractol_select = key - 17;
// 	else if (key == 23)
// 		g->fractol_select = 5;
// 	else if (key == 22)
// 		g->fractol_select = 6;
// 	else if (key == 26)
// 		g->fractol_select = 7;
// 	else if (key == 28)
// 		g->fractol_select = 8;
// 	if (key == RELOAD || (key > 17 && key < 23) || key == 26 || key == 28)
// 		globals_init(g);
// 	return (0);
// }

// static int	ft_keys_color(int key, t_global *g)
// {
// 	if (key == COLOR_PLUS)
// 	{
// 		g->fr.c_step_x += 1;
// 		g->fr.c_step_y += 1;
// 	}
// 	else if (key == COLOR_MINUS)
// 	{
// 		g->fr.c_step_x -= 1;
// 		g->fr.c_step_y -= 1;
// 	}
// 	else if (key == ALPHA_PLUS && g->fr.a_s < 255)
// 		g->fr.a_s += 5;
// 	else if (key == ALPHA_MINUS && g->fr.a_s > 4)
// 		g->fr.a_s -= 5;
// 	else
// 		ft_keys_select(key, g);
// 	return (0);
// }

int			ft_keys(int key, t_global *g)
{
	double pre_dir_x;
	double pre_plane_x;

	if (key == ESC)
	{
		system("leaks wolf3d > leaks");
		exit(0);
	}
	//move forward if no wall in front of you
	if (key == STRAFE_LEFT)
	{
		if (world_map[(int)(g->w.pos_x - g->w.dir_y * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x -= g->w.dir_y * g->w.move_speed;
		if (world_map[(int)g->w.pos_x][(int)(g->w.pos_y + g->w.dir_x * g->w.move_speed)] == 0)
			g->w.pos_y += g->w.dir_x * g->w.move_speed;

	}
	else if (key == STRAFE_RIGHT)
	{
		if (world_map[(int)(g->w.pos_x + g->w.dir_y * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x += g->w.dir_y * g->w.move_speed;
		if (world_map[(int)g->w.pos_x][(int)(g->w.pos_y - g->w.dir_x * g->w.move_speed)] == 0)
			g->w.pos_y -= g->w.dir_x * g->w.move_speed;
	}

	if (key == MOVE_UP || key == MOVE_W)
	{
		if (world_map[(int)(g->w.pos_x + g->w.dir_x * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x += g->w.dir_x * g->w.move_speed;
		if(world_map[(int)g->w.pos_x][(int)(g->w.pos_y + g->w.dir_y * g->w.move_speed)] == 0)
			g->w.pos_y += g->w.dir_y * g->w.move_speed;
	}
	//move backwards if no wall behind you
	else if (key == MOVE_DOWN || key == MOVE_S)
	{
		if (world_map[(int)(g->w.pos_x - g->w.dir_x * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x -= g->w.dir_x * g->w.move_speed;
		if(world_map[(int)g->w.pos_x][(int)(g->w.pos_y - g->w.dir_y * g->w.move_speed)] == 0)
			g->w.pos_y -= g->w.dir_y * g->w.move_speed;
	}
	if (key == ROT_LEFT)
	{
		pre_dir_x = g->w.dir_x;
		g->w.dir_x = g->w.dir_x * cos(g->w.rot_speed) - g->w.dir_y * sin(g->w.rot_speed);
		g->w.dir_y = pre_dir_x * sin(g->w.rot_speed) + g->w.dir_y * cos(g->w.rot_speed);
		pre_plane_x = g->w.plane_x;
		g->w.plane_x = g->w.plane_x * cos(g->w.rot_speed) - g->w.plane_y * sin(g->w.rot_speed);
		g->w.plane_y = pre_plane_x * sin(g->w.rot_speed) + g->w.plane_y * cos(g->w.rot_speed);
	}
	else if (key == ROT_RIGHT)
	{
		pre_dir_x = g->w.dir_x;
		g->w.dir_x = g->w.dir_x * cos(-g->w.rot_speed) - g->w.dir_y * sin(-g->w.rot_speed);
		g->w.dir_y = pre_dir_x * sin(-g->w.rot_speed) + g->w.dir_y * cos(-g->w.rot_speed);
		pre_plane_x = g->w.plane_x;
		g->w.plane_x = g->w.plane_x * cos(-g->w.rot_speed) - g->w.plane_y * sin(-g->w.rot_speed);
		g->w.plane_y = pre_plane_x * sin(-g->w.rot_speed) + g->w.plane_y * cos(-g->w.rot_speed);
	}
	if (key == RELOAD)
	{
		g->w.plane_y = 0.66;
		g->w.ampl_wall_high = 0;
	}

	ft_re_draw(g);
	return (0);
}
