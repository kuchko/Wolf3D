/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuchko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:52:34 by okuchko           #+#    #+#             */
/*   Updated: 2018/12/13 18:54:25 by okuchko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_listing(t_list **bgn, int fd)
{
	t_list	*tmp;
	t_list	*pre;

	if (!(*bgn))
	{
		if (!((*bgn) = ft_lstnew("\0", 1)))
			return (NULL);
		(*bgn)->content_size = fd;
		return (*bgn);
	}
	tmp = *bgn;
	while (tmp)
	{
		pre = tmp;
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = ft_lstnew("\0", 1)))
		return (NULL);
	tmp->content_size = fd;
	pre->next = tmp;
	return (tmp);
}

static int		ft_to_line(char **line, t_list *tmp)
{
	int			i;

	i = 0;
	while (tmp && ((char *)tmp->content)[i] &&
							(((char *)tmp->content)[i] != '\n'))
		i++;
	if (!(*line = ft_strnew(i)))
		return (-1);
	ft_strncpy(*line, tmp->content, i);
	return (1);
}

static int		ft_to_remain(t_list *this)
{
	char		*v;
	char		*u;

	u = this->content;
	v = (char*)ft_strchr(this->content, '\n');
	if (v && ft_strlen(v))
	{
		if (!(this->content = ft_strdup(v + 1)))
			return (-1);
		free(u);
		return (1);
	}
	if (!(this->content = ft_strnew(0)))
		return (-1);
	free(u);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*this;
	char			*buf;
	char			*u;
	int				ret;

	buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buf, 0) < 0
						|| !buf || !(this = ft_listing(&lst, fd)))
		return (-1);
	while (ft_count_char(this->content, '\n') == 0 &&
						(ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		u = this->content;
		if (ret == -1 || !(this->content = ft_strjoin(this->content, buf)))
			return (-1);
		free(u);
	}
	if (ft_to_line(line, this) == -1 || ft_to_remain(this) == -1)
		return (-1);
	free(buf);
	if (ret || ft_strlen(this->content) || ft_strlen(*line))
		return (1);
	return (0);
}
