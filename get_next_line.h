/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:34:47 by rschuppe          #+#    #+#             */
/*   Updated: 2018/12/07 12:34:48 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define BUFF_SIZE 32

typedef struct	s_rest_fd
{
	int			fd;
	char		*rest;
}				t_rest_fd;

int				get_next_line(const int fd, char **line);

#endif
