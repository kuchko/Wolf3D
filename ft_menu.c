/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:20:57 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:20:58 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// static void	ft_draw_menu_1(t_global *g, int o)
// {
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 500, 0xffd700,
// 		"<>                            change alpha channel");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 525, 0xffd700,
// 		"[]                                    change color");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 550, 0xffd700,
// 		"+                                          zoom in");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 575, 0xffd700,
// 		"-                                         zoom out");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 600, 0xffd700,
// 		"num +                          increase iterations");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 625, 0xffd700,
// 		"num -                          decrease iterations");
// }

// static void	ft_draw_menu_2(t_global *g, int o)
// {
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 650, 0xffd700,
// 		"left arrow                               move left");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 675, 0xffd700,
// 		"right arrow                             move right");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 700, 0xffd700,
// 		"up arrow                                   move up");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 725, 0xffd700,
// 		"down arrow                               move down");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 775, 0xffd700,
// 		"MOUSE left                                     pan");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 800, 0xffd700,
// 		"MOUSE middle                                  zoom");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 825, 0xffd700,
// 		"MOUSE right                                  color");
// }

// void		ft_draw_menu(t_global *g)
// {
// 	int	o;

// 	o = TEXT_OFFSET;
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, 620, 100, 0xff0000,
// 		"WELCOME to Fracol project by okuchko");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, 635, 250, 0x00ffff,
// 		"please, press any key to start:");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 300, 0xffd700,
// 		"1                                        Julia Set");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 325, 0xffd700,
// 		"2                                   Mandelbrot Set");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 350, 0xffd700,
// 		"3                                      Buffalo Set");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 375, 0xffd700,
// 		"4                                     Burning Ship");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 400, 0xffd700,
// 		"5                                     Burning Star");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 425, 0xffd700,
// 		"6                           Burning Ship 5th order");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 450, 0xffd700,
// 		"7                               Mandelbrot Tricorn");
// 	mlx_string_put(g->mlx_ptr, g->win_ptr, o, 475, 0xffd700,
// 		"8                             Mandelbrot 4th order");
// 	ft_draw_menu_1(g, o);
// 	ft_draw_menu_2(g, o);
// }
