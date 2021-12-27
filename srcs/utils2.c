/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:34:31 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 22:15:29 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			get_depth(t_minirt *data, t_camera *cam, int x, int y)
{
	data->depth = *(cam->buf->pixel + y * cam->buf->w + x);
	return (0);
}

int			set_depth(t_minirt *data, t_camera *cam, int x, int y)
{
	*(cam->buf->pixel + y * cam->buf->w + x) = data->depth;
	return (0);
}

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		free_camera(t_minirt *data)
{
	t_camera	*cam;
	void		*p;

	if (!data->cams_head)
		cam = data->cams;
	else
		cam = data->cams_head;
	while (cam)
	{
		p = cam->next;
		if (cam->base.img)
			mlx_destroy_image(data->mlx, cam->base.img);
		if (cam->buf)
			SAFE_FREE(cam->buf->pixel);
		SAFE_FREE(cam->buf);
		SAFE_FREE(cam);
		cam = p;
	}
}

void		free_minirt(t_minirt *data)
{
	void		*p;

	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	while (data->lights)
	{
		p = data->lights->next;
		SAFE_FREE(data->lights);
		data->lights = p;
	}
	while (data->objs)
	{
		p = data->objs->next;
		SAFE_FREE(data->objs);
		data->objs = p;
	}
	free_camera(data);
	// MLX_DESTROY_DISPLAY;
	SAFE_FREE(data->mlx);
}
