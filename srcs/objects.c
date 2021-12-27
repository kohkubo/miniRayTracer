/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:34:24 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 18:43:36 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	raytracing_sp(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2])
{
	double	t[2];
	int		i;

	if (solution(1, 2.0 * vdot(sn, vsub(s, obj->p1)),
			vectlen2(vsub(s, obj->p1)) - obj->rad * obj->rad, t) < EPSILON)
		return (-1.0);
	i = 0;
	while (i < 2)
	{
		if (0 < t[i])
		{
			if (lookat)
			{
				lookat[P] = vadd(s, vscale(sn, t[i]));
				lookat[N] = vunit(vsub(lookat[P], obj->p1));
				if (i == 1)
					lookat[N] = vscale(lookat[N], -1);
			}
			return (t[i]);
		}
		i++;
	}
	return (-1.0);
}

double	raytracing_tr(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2])
{
	t_vect	p[2];
	double	sn_dot_n;
	t_vect	vn[3];
	double	t;

	p[N] = vunit(vcross(vsub(obj->p2, obj->p1), vsub(obj->p1, obj->p3)));
	if ((sn_dot_n = vdot(sn, p[N])) == 0)
		return (-1.0);
	if ((t = vdot(vsub(obj->p1, s), p[N]) / sn_dot_n) < EPSILON)
		return (-1.0);
	p[P] = vadd(s, vscale(sn, t));
	vn[0] = vunit(vcross(vsub(p[P], obj->p1), vsub(obj->p2, obj->p1)));
	vn[1] = vunit(vcross(vsub(p[P], obj->p2), vsub(obj->p3, obj->p2)));
	vn[2] = vunit(vcross(vsub(p[P], obj->p3), vsub(obj->p1, obj->p3)));
	if (EPSILON < vdot(p[N], vn[0]) && EPSILON < vdot(p[N], vn[1])
												&& EPSILON < vdot(p[N], vn[2]))
	{
		if (lookat)
		{
			lookat[P] = p[P];
			lookat[N] = EPSILON > sn_dot_n ? p[N] : vscale(p[N], -1);
		}
		return (t);
	}
	return (-1.0);
}

double	raytracing_pl(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2])
{
	double	d_dot_n;
	double	t;

	if ((d_dot_n = vdot(sn, obj->n)) == 0)
		return (-1.0);
	if ((t = vdot(vsub(obj->p1, s), obj->n) / d_dot_n) < EPSILON)
		return (-1.0);
	if (lookat)
	{
		lookat[P] = vadd(s, vscale(sn, t));
		lookat[N] = EPSILON < d_dot_n ? vscale(obj->n, -1) : obj->n;
	}
	return (t);
}

double	raytracing_sq(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2])
{
	t_vect	c[2];
	double	t;
	double	v_dot_n;
	t_vect	p;
	double	l[2];

	if ((v_dot_n = vdot(sn, obj->n)) == 0)
		return (-1.0);
	unique_square(obj->n, c);
	if ((t = vdot(obj->n, vsub(obj->p1, s)) / v_dot_n) < 0)
		return (-1.0);
	p = vadd(s, vscale(sn, t));
	l[0] = fabs(vdot(vsub(p, obj->p1), c[0]));
	l[1] = fabs(vdot(vsub(p, obj->p1), c[1]));
	if (EPSILON < obj->half_size - l[0] && EPSILON < obj->half_size - l[1])
	{
		if (lookat)
		{
			lookat[P] = p;
			lookat[N] = 0 < v_dot_n ? vscale(obj->n, -1) : obj->n;
		}
		return (t);
	}
	return (-1.0);
}

void	camera_on(t_minirt *data)
{
	t_camera	*cam;

	cam = data->cams;
	while (cam)
	{
		buf_init(data, cam);
		base_init(data, cam);
		scene_init(&cam->base, data->scene);
		draw_scene(data, cam);
		cam = cam->next;
	}
	minirt_mlx_loop(data);
}
