/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:12:10 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 00:07:28 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

#define FD_MAX 1024
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

#define ERROR -1
#define CONTINUE 1
#define END 0

static char *ft_strn(char *s)
{
	while (*s && *s != '\n')
		s++;
	return (s);
}

static int is_n(char *s)
{
	while (*s && *s != '\n')
		s++;
	return (*s == '\n');
}

static int store_line(char **line, char **s)
{
	char *tmp;
	char *dst;

	tmp = *s;
	if (!(dst = malloc(ft_strn(tmp) - tmp + 1)))
	{
		SAFE_FREE(*s);
		return (ERROR);
	}
	*line = dst;
	while (*tmp && *tmp != '\n')
		*dst++ = *tmp++;
	*dst = '\0';
	if (*tmp == '\0')
	{
		SAFE_FREE(*s);
		return (END);
	}
	else
		*s = free_return(s, ft_strjoin(++tmp, ""));
	return (CONTINUE);
}

static int read_file(int fd, char **s)
{
	char *buf;
	ssize_t rc;

	if (!(buf = malloc((size_t)BUFFER_SIZE + 1)))
		return (ERROR);
	rc = 1;
	while (0 < rc && !is_n(*s))
	{
		if ((rc = read(fd, buf, BUFFER_SIZE)) < 0)
		{
			SAFE_FREE(buf);
			SAFE_FREE(*s);
			return (ERROR);
		}
		buf[rc] = '\0';
		if (!(*s = free_return(s, ft_strjoin(*s, buf))))
			return (ERROR);
	}
	SAFE_FREE(buf);
	if (rc == 0)
		return (END);
	return (CONTINUE);
}

int ft_get_next_line(int fd, char **line)
{
	static char *s[FD_MAX];

	if (!line || BUFFER_SIZE <= 0 || read(fd, 0, 0) == ERROR)
		return (ERROR);
	if (s[fd] == NULL)
	{
		if (!(s[fd] = malloc(1)))
			return (ERROR);
		*s[fd] = '\0';
	}
	if (read_file(fd, &s[fd]) == ERROR)
		return (ERROR);
	return (store_line(line, &s[fd]));
}