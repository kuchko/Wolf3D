/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:22:17 by okuchko           #+#    #+#             */
/*   Updated: 2019/07/25 17:22:19 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void		globals_init(t_global *g)
{
	ft_bzero(&g->fr, sizeof(g->fr));
	g->fr.zoom = 1;
	g->fr.zoom_step = 1.2;
	g->fr.max_iterations = 40;
	g->fr.c_re = -0.7;
	g->fr.c_im = 0.27015;
}

static void	ft_input_select(int argc, char **argv, t_global *g)
{
	if (argc == 1)
	{
		ft_printf("usage:	wolf3d map_file\n");
		ft_error("map_file - is rectangualr shaped map max [100,100] sized \n");
	}
}

int			main(int argc, char **argv)
{
	t_global	g;

	ft_input_select(argc, argv, &g);
	globals_init(&g);
	ft_draw(&g);
	system("leaks fractol > leaks");
	return (0);
}
