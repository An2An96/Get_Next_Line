/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:34:33 by rschuppe          #+#    #+#             */
/*   Updated: 2018/12/10 21:09:43 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*find_element_by_fd(t_list **alst, const int fd)
{
	t_list		*tmp;
	t_list		*new;
	t_rest_fd	*content;

	tmp = *alst;
	while (tmp)
	{
		if (((t_rest_fd*)(tmp->content))->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	content = (t_rest_fd*)malloc(sizeof(t_rest_fd));
	content->fd = fd;
	content->rest = NULL;
	new = ft_lstnew(content, sizeof(t_rest_fd));
	if (new)
		ft_lstadd(alst, new);
	return (new);
}

static int		get_line_in_string(char **str, char **result)
{
	char	*ptr;

	if (str && *str)
	{
		ptr = ft_strchr(*str, '\n');
		if (ptr)
		{
			*ptr = '\0';
			*result = ft_strdup(*str);
			if (*(ptr + 1))
				ptr = ft_strdup(ptr + 1);
			else
				ptr = NULL;
			free(*str);
			*str = ptr;
			return (1);
		}
		else
		{
			*result = ft_strdup(*str);
			free(*str);
			*str = NULL;
		}
	}
	return (0);
}

static int		read_line_fd(const int fd, char **line, char **rest)
{
	char	buf[BUFF_SIZE + 1];
	int		readed_len;
	char	*tmp;
	int		res;

	while ((readed_len = read(fd, buf, BUFF_SIZE)) != -1)
	{
		if (readed_len == 0)
			return (*line ? 1 : 0);
		buf[readed_len] = '\0';
		tmp = ft_strjoin(*rest, buf);
		free(*rest);
		*rest = tmp;
		res = get_line_in_string(rest, &tmp);
		tmp = ft_strjoin(*line, tmp);
		free(*line);
		*line = tmp;
		if (res || readed_len < BUFF_SIZE)
			return (1);
	}
	return (-1);
}

void			clear_fd(void *content, size_t content_size)
{
	content_size = 0;
	free(content);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*fd_rest_list;
	t_list			*fd_rest_el;
	t_rest_fd		*cur_fd_rest;
	char			*line_tmp;
	int				read_res;

	read_res = -1;
	line_tmp = NULL;
	if (fd >= 0)
	{
		fd_rest_el = find_element_by_fd(&fd_rest_list, fd);
		if (fd_rest_el)
		{
			cur_fd_rest = (t_rest_fd*)(fd_rest_el->content);
			read_res = get_line_in_string(&(cur_fd_rest->rest), &line_tmp);
			if (read_res == 0)
				read_res = read_line_fd(fd, &line_tmp, &(cur_fd_rest->rest));
			if (read_res > 0)
				*line = line_tmp;
			// else
			// 	ft_lstremove(&fd_rest_list, fd_rest_el, clear_fd);
		}
	}
	return (read_res);
}
