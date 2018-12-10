/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:34:33 by rschuppe          #+#    #+#             */
/*   Updated: 2018/12/07 12:34:34 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void read_line_fd(const int fd, char **line, char **rest)
{
	char	buf[BUFF_SIZE];
	int		readed_len;
	char	*chr_ptr;
	char	*tmp;

	chr_ptr = NULL;
	while ((readed_len = read(fd, buf, BUFF_SIZE)))
	{
		buf[readed_len] = '\0';
		chr_ptr = ft_strchr(buf, '\n');
		if (chr_ptr)
			*chr_ptr = '\0';
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
		if (chr_ptr)
		{
			tmp = ft_strjoin(*rest, chr_ptr + 1);
			free(*rest);
			*rest = tmp;
			break ;
		}
	}
}

static t_list	*find_element_by_fd(t_list *alst, const int fd)
{
	t_list		*first;
	t_list		*new;
	t_rest_fd	*content;

	first = alst;
	while (alst)
	{
		if (((t_rest_fd*)(alst->content))->fd == fd)
			return (alst);
		alst = alst->next;
	}
	content = (t_rest_fd*)malloc(sizeof(t_rest_fd));
	content->fd = fd;
	content->rest = NULL;
	new = ft_lstnew(content, sizeof(t_rest_fd));
	if (new)
		ft_lstadd(first, new);
	return (new);
}

int	get_next_line(const int fd, char **line)
{
	static t_list	*fd_rest_list;
	t_list			*fd_rest;
	char			*result;
	char			*tmp;

	fd_rest = find_element_by_fd(fd_rest_list, fd);

	// if (ft_strlen(((t_rest_fd*)(fd_rest->content))->rest)
	// {
	// 	tmp = ft_strjoin(result, ((t_rest_fd*)(fd_rest->content))->rest)
	// }

	read_line_fd(fd, &result, &(((t_rest_fd*)(fd_rest->content))->rest));
}

// t_list	*ft_lstfind(t_list *alst, int (*f)(void *, size_t))
// {
// 	if (alst && f)
// 	{
// 		if (f(alst->content, alst->content_size))
// 			return (alst);
// 		else
// 			return (ft_lstfind(alst->next, f));
// 	}
// 	return (NULL);
// }
