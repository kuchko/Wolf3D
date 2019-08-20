/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:42:22 by okuchko           #+#    #+#             */
/*   Updated: 2019/08/20 17:42:24 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_show_list(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void		ft_show_map(t_wolf *w)
{
	int	x;
	int y;

	y = -1;
	ft_printf("map[%d][%d] - position(%f,%f):\n", w->map_size_y,
		w->map_size_x, w->pos_y, w->pos_x);
	while (++y < w->map_size_y)
	{
		x = -1;
		while (++x < w->map_size_x)
		{
			ft_printf("%d ", w->map[y][x]);
		}
		ft_printf("\n");
	}
}

static int	ft_valid_symbols(t_list *lst, int y_range)
{
	int	i;
	int	j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (((char*)lst->content)[j])
			if (ft_strchr("012,", ((char*)lst->content)[j++]) == NULL)
				return (0);
		lst = lst->next;
		i++;
	}
	if (i == y_range)
		return (1);
	return (0);
}

static int	ft_read_to_list(t_list **start, int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char	*l;
	int		i;

	i = 0;
	while (get_next_line(fd, &l) > 0 && ++i)
	{
		if (*start == NULL)
		{
			if ((*start = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst = *start;
		}
		else
		{
			if ((tmp = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst->next = tmp;
			lst = tmp;
		}
		free(l);
	}
	i > 0 ? free(l) : 0;
	return (i);
}

void		ft_read(t_global *g, t_list **start, int argc, char **argv)
{
	int		fd;

	*start = NULL;
	if (argc == 1)
		ft_error("usage:	wolf3D map_file\n");
	if (argc > 2)
		ft_error("wolf3D must have only one map_file\n");
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
		ft_error("open directory is invalid\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error("open map_file error\n");
	if ((g->w.map_size_y = ft_read_to_list(start, fd)) == 0)
		ft_error("invalid file content\n");
	close(fd);
	if (g->w.map_size_y > 100)
		ft_error("map is too big\n");
	if (ft_valid_symbols(*start, g->w.map_size_y) == 0)
		ft_error("invalid symbols in file\n");
	if (!ft_validate_map(*start, &g->w))
		ft_error("map error. coordinates might be out of range.\n");
}
