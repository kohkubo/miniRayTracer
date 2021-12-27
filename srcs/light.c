/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:30:17 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/03 19:42:41 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vect_light(t_light *light, t_camera *cam)
{
	t_vect	r;
	t_vect	v;

	light->lookat_to_light = vsub(light->p, cam->lookat[P]);
	light->lookat_to_light_unit = vunit(light->lookat_to_light);
	light->lightlen = vectlen(light->lookat_to_light);
	light->cos1 = vdot(light->lookat_to_light_unit, cam->lookat[N]);
	r = vsub(vscale(cam->lookat[N], vdot(cam->lookat[N],
		light->lookat_to_light_unit) * 2), light->lookat_to_light_unit);
	v = vscale(cam->view, -1);
	light->cos2 = vdot(v, r);
}

void	objs_reflection(t_objs *objs, t_light *light)
{
	int		c;
	double	diff;
	double	spec;

	c = 0;
	while (c < 3)
	{
		diff = objs->mat.diff[c] * light->range * light->cos1 * light->color[c];
		spec = objs->mat.spec[c] * light->range * light->cosf * light->color[c];
		objs->shade[c] += diff + spec;
		c++;
	}
}

void	objs_color(t_minirt *data, t_objs *objs)
{
	int	c;
	int	color[3];

	c = 0;
	while (c < 3)
	{
		objs->shade[c] +=
					objs->mat.diff[c] * data->ambl.range * data->ambl.color[c];
		if (1.0 < objs->shade[c])
			objs->shade[c] = 1.0;
		color[c] = (t_pix)(255 * objs->shade[c]);
		c++;
	}
	data->color = create_trgb(0, color[R], color[G], color[B]);
}

void	shadowing(t_minirt *data, t_objs *objs, t_light *light, t_camera *cam)
{
	t_objs	*tmp;
	double	t;

	(void)objs;
	tmp = data->objs;
	while (tmp)
	{
		t = data->raytracing[tmp->id](tmp,
			vadd(cam->lookat[P], vscale(light->lookat_to_light_unit, EPSILON)),
											light->lookat_to_light_unit, NULL);
		if (0 < t && t < light->lightlen)
		{
			light->cos1 = 0.0;
			light->cosf = 0.0;
			break ;
		}
		tmp = tmp->next;
	}
}

void	lighting(t_minirt *data, t_objs *objs, t_camera *cam)
{
	t_light	*light;

	objs->shade[0] = 0;
	objs->shade[1] = 0;
	objs->shade[2] = 0;
	light = data->lights;
	while (light)
	{
		vect_light(light, cam);
		if (light->cos1 < EPSILON)
			light->cos1 = 0.0;
		light->cosf = light->cos2 < EPSILON ?
										0.0 : pow(light->cos2, objs->mat.high);
		shadowing(data, objs, light, cam);
		objs_reflection(objs, light);
		light = light->next;
	}
	objs_color(data, objs);
}
