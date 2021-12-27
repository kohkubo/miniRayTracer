/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:08:49 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 20:32:28 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_status	store_scene(char **info, t_scene *scene)
{
	double	w;
	double	h;

	if (!is_n_split(info, 3) || scene->color_bg != -1)
		return (ERROR);
	if (is_n_char(info[RESOLU_X], 0, 0) || is_n_char(info[RESOLU_Y], 0, 0))
		return (ERROR);
	w = ft_atof(info[RESOLU_X]);
	h = ft_atof(info[RESOLU_Y]);
	if (w < 1 || h < 1 || IS_INF(w) || IS_INF(h) ||
			IS_RANGE(w, 4000, INFINITY) || IS_RANGE(h, 4000, INFINITY))
		return (ERROR);
	if (scene->h == INFINITY)
	{
		scene->h = (int)h;
		scene->w = (int)w;
	}
	else
	{
		scene->h = scene->h < h ? (int)scene->h : (int)h;
		scene->w = scene->w < w ? (int)scene->w : (int)w;
	}
	scene->color_bg = create_trgb(0, 0, 0, 0);
	return (SUCCESS);
}

t_status	store_ambl(char **info, t_ambl *ambl)
{
	if (!is_n_split(info, 3) || ambl->range != -1)
		return (ERROR);
	ambl->range = ft_atof(info[AMBL_RANGE]);
	if (!IS_RANGE(ambl->range, 0.0, 1.0))
		return (ERROR);
	if (store_color(info[AMBL_RGB], ambl->color) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

t_status	store_light(t_minirt *data, char **info)
{
	t_light		*lights;
	t_status	flg;

	if (!is_n_split(info, 4))
		return (ERROR);
	if (!(lights = malloc(sizeof(t_light))))
		return (ERROR);
	lights->p = ato_vect(info[LIGHT_POS]);
	lights->range = ft_atof(info[LIGHT_RANGE]);
	flg = store_color(info[LIGHT_RGB], lights->color);
	lights->next = NULL;
	if (data->lights)
		lights->next = data->lights;
	data->lights = lights;
	if (!IS_RANGE(lights->range, -EPSILON, 1.0) || flg == ERROR ||
															is_vinf(lights->p))
		return (ERROR);
	return (SUCCESS);
}

t_status	store_camera(t_minirt *data, char **info)
{
	t_camera	*cams;

	if (!is_n_split(info, 4))
		return (ERROR);
	if (!(cams = malloc(sizeof(t_camera))))
		return (ERROR);
	cams->p = ato_vect(info[CAMERA_POS]);
	cams->n = ato_vect(info[CAMERA_NOV]);
	if (is_vrange(cams->n, -1.0, 1.0) && !is_vzero(cams->n))
		cams->n = vunit(cams->n);
	else
		cams->n = VERROR;
	cams->fov = (int)ft_atof(info[CAMERA_FOV]);
	cams->buf = NULL;
	cams->next = NULL;
	cams->base.img = NULL;
	if (data->cams)
		cams->next = data->cams;
	data->cams = cams;
	if (!IS_RANGE(cams->fov, 1, 179) || is_vinf(cams->n) || is_vinf(cams->p))
		return (ERROR);
	return (SUCCESS);
}

t_status	store_mat(char *s, t_mat *mat)
{
	if (store_color(s, mat->diff) == ERROR)
		return (ERROR);
	mat->spec[R] = 0.9;
	mat->spec[G] = 0.9;
	mat->spec[B] = 0.9;
	mat->high = 20.0;
	return (SUCCESS);
}
