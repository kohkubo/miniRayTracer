/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:47:31 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 18:47:31 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	solution(double a, double b, double c, double t[2])
{
	double	d;

	d = (b * b) - (4.0 * a * c);
	if (d < EPSILON)
		return (-1.0);
	t[0] = (b + sqrt(d)) / (-2.0 * a);
	t[1] = (b - sqrt(d)) / (-2.0 * a);
	return (d);
}

double	raytracing_cy_sub(t_objs *obj, t_vect p[2], double t[2], t_vect at[2])
{
	double	tmp[2];
	int		i;

	tmp[0] = vdot(vsub(p[0], obj->p1), obj->n);
	tmp[1] = vdot(vsub(p[1], obj->p1), obj->n);
	i = 0;
	while (i < 2)
	{
		if (0 < t[i])
			if (0 <= tmp[i] && tmp[i] <= obj->height)
			{
				if (at)
				{
					at[P] = p[i];
					at[N] = vunit(vsub(vsub(p[i],
											obj->p1), vscale(obj->n, tmp[i])));
					if (i == 1)
						at[N] = vscale(at[N], -1);
				}
				return (t[i]);
			}
		i++;
	}
	return (-1.0);
}

double	raytracing_cy(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2])
{
	double	t[2];
	t_vect	p[2];
	t_vect	view_x_n;
	t_vect	c_p_x_n;

	view_x_n = vcross(sn, obj->n);
	c_p_x_n = vcross(vsub(s, obj->p1), obj->n);
	if (solution(vectlen2(view_x_n), 2.0 * vdot(view_x_n, c_p_x_n),
					vectlen2(c_p_x_n) - (obj->rad * obj->rad), t) < EPSILON)
		return (-1.0);
	p[0] = vadd(s, vscale(sn, t[0]));
	p[1] = vadd(s, vscale(sn, t[1]));
	return (raytracing_cy_sub(obj, p, t, lookat));
}

void	unique_square(t_vect n, t_vect center[2])
{
	double	a1;
	double	a3;

	if (n.x == 0 && n.z == 0)
		center[0] = init_vect(-1, 0, 0);
	else
	{
		a1 = n.z / sqrt(n.x * n.x + n.z * n.z);
		a3 = n.x / sqrt(n.x * n.x + n.z * n.z);
		center[0] = init_vect(-a1, 0, a3);
	}
	center[1] = vcross(center[0], vscale(n, -1));
}
