/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:19:00 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 21:12:15 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_store_info	g_store_info[7];

void		pixel_put(t_minirt *data, t_camera *c, int x, int y)
{
	t_objs	*objs;
	double	t;

	get_depth(data, c, x, y);
	objs = data->objs;
	while (objs)
	{
		t = data->raytracing[objs->id](objs, c->p, c->view, c->lookat);
		if (t < EPSILON || EPSILON < t - data->depth)
			objs = objs->next;
		else
		{
			data->depth = t;
			set_depth(data, c, x, y);
			lighting(data, objs, c);
			my_mlx_pixel_put(&(c->base), x, y, data->color);
			objs = objs->next;
		}
	}
}

void		draw_scene(t_minirt *data, t_camera *cam)
{
	int		x;
	int		y;
	t_vect	center[2];
	t_vect	s;

	cam->focal_len = data->scene.w / (tan((PI / 180) * (cam->fov / 2)) * 2);
	cam->scene_center = vscale(cam->n, cam->focal_len);
	unique_square(cam->n, center);
	y = 0;
	while (y < data->scene.h)
	{
		x = 0;
		while (x < data->scene.w)
		{
			s = vadd(vscale(center[0], data->scene.w / 2 - x),
									vscale(center[1], y - data->scene.h / 2));
			cam->view = vunit(vadd(cam->scene_center, s));
			pixel_put(data, cam, x, y);
			x++;
		}
		y++;
	}
}

t_status	store_info(t_minirt *data, char **info)
{
	t_objs_id	id;

	id = objs_id(info);
	if (id != UNKNOWN)
		return (g_store_info[id](data, info));
	return (ERROR);
}

void		read_file(t_minirt *data)
{
	char		*line;
	int8_t		rc;
	t_status	flg;

	rc = 1;
	while (rc)
	{
		if ((rc = ft_get_next_line(data->fd, &line)) == 1)
		{
			if (line[0] == '#' || !line[0] || ft_isspace(line[0]))
			{
				SAFE_FREE(line);
				continue ;
			}
			flg = parse_line(data, line);
		}
		SAFE_FREE(line);
		if (rc == -1 || flg == ERROR)
			error_end(data, "read file error");
	}
}

int			main(int ac, char **av)
{
	t_minirt	data;

	init_store_info(g_store_info);
	minirt_init(&data);
	validate_args(&data, ac, av);
	read_file(&data);
	init_window(&data);
	if (data.bmp)
		bmp_make(&data);
	else
		camera_on(&data);
}
