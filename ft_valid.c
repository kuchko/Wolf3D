/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:42:34 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:42:35 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_get_x_range(t_list *lst)
{
	char	**c;
	int		i;

	i = 0;
	if ((c = ft_strsplit(lst->content, ',')) == NULL)
		return (0);
	while (c[i])
		i++;
	ft_strdoublefree(c);
	return (i);
}

static int	ft_check_line_is_map_closed_and_rect(t_wolf *w, t_list *lst, int j)
{
	int		l;
	char	*str;

	str = lst->content;
	l = ft_strlen(lst->content);
	if (l < 5 || str[0] == '0' || str[l - 1] == '0')
		return (0);
	if ((j == 0 || j == w->map_size_y - 1) && ft_count_char(str, '0'))
		return (0);
	if (ft_get_x_range(lst) != w->map_size_x)
		return (0);
	return (1);
}

static void	ft_set_first_start(t_wolf *w, int j, int i)
{
	if (w->pos_x == 0.0 && w->pos_y == 0.0 && w->map[j][i] == 0)
	{
		w->pos_x = (double)j + 0.5;
		w->pos_y = (double)i + 0.5;
		w->pos_start_x = w->pos_x;
		w->pos_start_y = w->pos_y;
	}
}

static int	ft_map_load_from_list(t_list *lst, t_wolf *w)
{
	char	**c;
	int		i;
	int		j;

	j = -1;
	while (lst && (++j + 1))
	{
		if (ft_check_line_is_map_closed_and_rect(w, lst, j) == 0 ||
								(c = ft_strsplit(lst->content, ',')) == NULL)
			return (0);
		i = -1;
		while (c[++i])
		{
			w->map[j][i] = ft_atoi(c[i]);
			ft_set_first_start(w, j, i);
			if (w->map[j][i] < 0 || w->map[j][i] > 2 || ft_strlen(c[i]) > 1)
			{
				ft_strdoublefree(c);
				return (0);
			}
		}
		lst = lst->next;
		ft_strdoublefree(c);
	}
	return (1);
}

int			ft_validate_map(t_list *lst, t_wolf *w)
{
	if ((w->map_size_x = ft_get_x_range(lst)) == 0)
		ft_error("No split char ',' in line\n");
	if (w->map_size_x < 3 || w->map_size_x > 100)
		ft_error("Map lines must be between 3 and 100 coordinates\n");
	if (!(w->map = (int**)ft_double_malloc(sizeof(int),
										w->map_size_y, w->map_size_x)))
		ft_error("Double malloc error\n");
	if (!(ft_map_load_from_list(lst, w)))
		ft_error("Error in lines\n");
	if (w->pos_x == 0.0 || w->plane_x == 0.0)
		ft_error("No free place for player on map\n");
	return (1);
}
