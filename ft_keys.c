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
	if (key == SPACE)
		g->k.space = 1;
	if (key == RELOAD)
		g->k.enter = 1;
	if (key == SPEED_PLUS)
		g->k.plus = 1;
	else if (key == SPEED_MINUS)
		g->k.minus = 1;
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
	if (key == SPEED_PLUS)
		g->k.plus = 0;
	else if (key == SPEED_MINUS)
		g->k.minus = 0;
	return (0);
}

int			ft_keys(t_keys *k, t_global *g)
{
	double pre_dir_x;
	double pre_plane_x;

	// if (g->w.tex_flag == 1)
	// {
	// 	if (world_map[(int)(g->w.pos_x + g->w.dir_x * g->w.friction_speed)][(int)g->w.pos_y] == 0)
	// 		g->w.pos_x += g->w.dir_x * g->w.friction_speed;
	// 	if(world_map[(int)g->w.pos_x][(int)(g->w.pos_y + g->w.dir_y * g->w.friction_speed)] == 0)
	// 		g->w.pos_y += g->w.dir_y * g->w.friction_speed;
	// }

	if (k->esc)
	{
		system("leaks wolf3d > leaks");
		exit(0);
	}
	//move forward if no wall in front of you
	if (k->strafe_left)
	{
		if (world_map[(int)(g->w.pos_x - g->w.dir_y * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x -= g->w.dir_y * g->w.move_speed;
		if (world_map[(int)g->w.pos_x][(int)(g->w.pos_y + g->w.dir_x * g->w.move_speed)] == 0)
			g->w.pos_y += g->w.dir_x * g->w.move_speed;

	}
	else if (k->strafe_right)
	{
		if (world_map[(int)(g->w.pos_x + g->w.dir_y * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x += g->w.dir_y * g->w.move_speed;
		if (world_map[(int)g->w.pos_x][(int)(g->w.pos_y - g->w.dir_x * g->w.move_speed)] == 0)
			g->w.pos_y -= g->w.dir_x * g->w.move_speed;
	}

	if (k->move_forward)
	{
		if (world_map[(int)(g->w.pos_x + g->w.dir_x * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x += g->w.dir_x * g->w.move_speed;
		if(world_map[(int)g->w.pos_x][(int)(g->w.pos_y + g->w.dir_y * g->w.move_speed)] == 0)
			g->w.pos_y += g->w.dir_y * g->w.move_speed;
	}
	//move backwards if no wall behind you
	else if (k->move_back)
	{
		if (world_map[(int)(g->w.pos_x - g->w.dir_x * g->w.move_speed)][(int)g->w.pos_y] == 0)
			g->w.pos_x -= g->w.dir_x * g->w.move_speed;
		if(world_map[(int)g->w.pos_x][(int)(g->w.pos_y - g->w.dir_y * g->w.move_speed)] == 0)
			g->w.pos_y -= g->w.dir_y * g->w.move_speed;
	}
	if (k->rot_left)
	{
		pre_dir_x = g->w.dir_x;
		g->w.dir_x = g->w.dir_x * cos(g->w.rot_speed) - g->w.dir_y * sin(g->w.rot_speed);
		g->w.dir_y = pre_dir_x * sin(g->w.rot_speed) + g->w.dir_y * cos(g->w.rot_speed);
		pre_plane_x = g->w.plane_x;
		g->w.plane_x = g->w.plane_x * cos(g->w.rot_speed) - g->w.plane_y * sin(g->w.rot_speed);
		g->w.plane_y = pre_plane_x * sin(g->w.rot_speed) + g->w.plane_y * cos(g->w.rot_speed);
	}
	else if (k->rot_left)
	{
		pre_dir_x = g->w.dir_x;
		g->w.dir_x = g->w.dir_x * cos(-g->w.rot_speed) - g->w.dir_y * sin(-g->w.rot_speed);
		g->w.dir_y = pre_dir_x * sin(-g->w.rot_speed) + g->w.dir_y * cos(-g->w.rot_speed);
		pre_plane_x = g->w.plane_x;
		g->w.plane_x = g->w.plane_x * cos(-g->w.rot_speed) - g->w.plane_y * sin(-g->w.rot_speed);
		g->w.plane_y = pre_plane_x * sin(-g->w.rot_speed) + g->w.plane_y * cos(-g->w.rot_speed);
	}
	if (k->space)
	{
		g->w.tex_flag = g->w.tex_flag == 0 ? 1 : 0;
	}

	if (k->enter)
	{
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
	}

	if (k->plus && g->w.move_speed < 1.0)
		g->w.move_speed += g->w.frame_time * 2.0;
	else if (k->minus && g->w.move_speed > 0.12)
		g->w.move_speed -= g->w.frame_time * 2.0;

	// ft_re_draw(g);
	return (0);
}
