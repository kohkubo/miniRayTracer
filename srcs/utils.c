/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:14:49 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 21:14:24 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		error_end(t_minirt *data, char *s)
{
	ft_putstr_fd(s, 2);
	free_minirt(data);
	exit(EXIT_FAILURE);
}

void		validate_args(t_minirt *data, int ac, char **av)
{
	if (ac < 2 || 3 < ac)
		error_end(data, "error : file path");
	if (ac == 3)
	{
		if (ft_strncmp(av[2], "--save", 7))
			error_end(data, "error : file path");
		data->bmp = 1;
		data->scene.h = INFINITY;
	}
	if (ft_strlen(av[1]) < 3 || ft_strrncmp(av[1], ".rt", 3) ||
								(data->fd = open(av[1], O_RDONLY)) == -1)
		error_end(data, "error : file path");
	ft_strlcpy(data->path, av[1], SIZE_MAX);
}

t_status	parse_line(t_minirt *data, char *line)
{
	char		**info;
	t_status	flg;

	if (!(info = ft_split_charset(line, " \t\v\f\r")))
		return (ERROR);
	if (!ft_strcmp(info[0], "R"))
		flg = store_scene(info, &(data->scene));
	else if (!ft_strcmp(info[0], "A"))
		flg = store_ambl(info, &(data->ambl));
	else
		flg = store_info(data, info);
	free_ss(&info);
	if (flg == ERROR)
		return (ERROR);
	return (SUCCESS);
}

t_status	buf_init(t_minirt *data, t_camera *cam)
{
	double	*p;
	int		x;
	int		y;

	if (!(cam->buf = malloc(sizeof(t_buf))))
		return (ERROR);
	cam->buf->pixel = NULL;
	cam->buf->w = data->scene.w;
	cam->buf->h = data->scene.h;
	if (!(cam->buf->pixel = malloc(data->scene.w *
											data->scene.h * sizeof(double))))
	{
		SAFE_FREE(cam->buf);
		return (ERROR);
	}
	p = cam->buf->pixel;
	y = 0;
	while (y < cam->buf->h)
	{
		x = 0;
		while (x++ < cam->buf->w)
			*p++ = INFINITY;
		y++;
	}
	return (SUCCESS);
}

void		init_window(t_minirt *data)
{
	if (data->scene.color_bg == -1)
		error_end(data, "read file error\n");
	if (!data->lights)
		if ((parse_line(data, "l 0,0,0 0 0,0,0")) == ERROR)
			error_end(data, "read file error");
	if (data->ambl.range == -1)
		data->ambl.range = 0;
	if (!data->cams || !data->objs)
	{
		if (data->bmp == 1)
			error_end(data, "no window data");
		else
			minirt_mlx_loop(data);
	}
	data->cams_head = data->cams;
}
