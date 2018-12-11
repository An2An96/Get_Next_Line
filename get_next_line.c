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

static int	get_line_in_string(char **str, char **result)
{
	char	*ptr;
	char	*tmp;

	if (str && *str)
	{
		ptr = ft_strchr(*str, '\n');
		if (ptr)
			*ptr = '\0';
		if ((tmp = ft_strjoin(*result, *str)) == NULL)
			return (-1);
		ft_strdel(result);
		*result = tmp;
		tmp = NULL;
		if (ptr && *(ptr + 1))
		{
			if ((tmp = ft_strdup(ptr + 1)) == NULL)
				return (-1);
		}
		ft_strdel(str);
		*str = tmp;
		return (ptr ? 1 : 0);
	}
	return (0);
}

static int	read_line_fd(const int fd, char *buf, char **line, char **rest)
{
	int		readed_len;
	char	*tmp;
	int		res;

	if (buf)
	{
		while ((readed_len = read(fd, buf, BUFF_SIZE)) != -1)
		{
			if (readed_len == 0)
				return (*line ? 1 : 0);
			buf[readed_len] = '\0';
			if ((tmp = ft_strjoin(*rest, buf)) == NULL)
				return (-1);
			free(*rest);
			*rest = tmp;
			if ((res = get_line_in_string(rest, line)) == -1)
				return (-1);
			if (res || readed_len < BUFF_SIZE)
				return (1);
		}
	}
	return (-1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*rest_fd[MAX_FD];
	char			*buf;
	char			*line_tmp;
	int				read_res;

	if (fd < 0 || fd >= MAX_FD)
		return (-1);
	line_tmp = NULL;
	buf = NULL;
	if ((read_res = get_line_in_string(&rest_fd[fd], &line_tmp)) == 0)
	{
		buf = ft_strnew(BUFF_SIZE);
		read_res = read_line_fd(fd, buf, &line_tmp, &rest_fd[fd]);
	}
	if (read_res > 0)
		*line = line_tmp;
	else if (read_res == -1)
	{
		free(line_tmp);
		free(rest_fd[fd]);
	}
	else
		free(rest_fd[fd]);
	free(buf);
	return (read_res);
}
