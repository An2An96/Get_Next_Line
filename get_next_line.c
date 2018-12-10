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
	//printf("NEW ELEMENT: fd = %d, rest = %s\n", ((t_rest_fd*)(new->content))->fd, ((t_rest_fd*)(new->content))->rest);
	return (new);
}

static int	get_line_in_string(char **str, char **result)
{
	char	*ptr;
	//char	*tmp;

	if (str && *str)
	{
		ptr = ft_strchr(*str, '\n');
		if (ptr)
		{
			*ptr = '\0';
			*result = ft_strdup(*str);
			//*result = ft_strsub(*str, 0, ptr - *str);
			ptr = ft_strdup(ptr + 1);
			//ptr = ft_strsub(*str, (size_t)(ptr + 1), ft_strlen(ptr + 1));
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

static int read_line_fd(const int fd, char **line, char **rest)
{
	char	buf[BUFF_SIZE];
	int		readed_len;
	char	*tmp;
	int 	res;

	while ((readed_len = read(fd, buf, BUFF_SIZE)))
	{
		buf[readed_len] = '\0';

		tmp = ft_strjoin(*rest, buf);
		free(*rest);
		*rest = tmp;

		//printf("read: %s %s", buf, *rest);

		res = get_line_in_string(rest, &tmp);
		
		tmp = ft_strjoin(*line, tmp);
		free(*line);
		*line = tmp;
		
		if (res || readed_len < BUFF_SIZE)
			return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_list	*fd_rest_list;
	t_list			*fd_rest;
	t_rest_fd		*cur_fd_rest;

	fd_rest = find_element_by_fd(&fd_rest_list, fd);
	if (fd_rest)
	{
		cur_fd_rest = (t_rest_fd*)(fd_rest->content);
		//printf("el: fd = %d, rest = %s\n", cur_fd_rest->fd, cur_fd_rest->rest);
		if (get_line_in_string(&(cur_fd_rest->rest), line) == 0)
		{
			read_line_fd(fd, line, &(cur_fd_rest->rest));
		}
		return (ft_strlen(cur_fd_rest->rest) ? 1 : 0);
	}
	return (-1);
}
