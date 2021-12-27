/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:25:43 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 11:24:59 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBVECT_H
# define LIBVECT_H
# include <math.h>

typedef struct	s_vect
{
	double		x;
	double		y;
	double		z;
}				t_vect;

#ifndef TBOOL
# define TBOOL
typedef enum	e_bool
{
	FALSE = 0,
	TRUE
}				t_bool;
#endif

# define VERROR (init_vect(INFINITY, INFINITY, INFINITY))

double	vdot(t_vect a, t_vect b);
double	vectlen(t_vect v);
double	vectlen2(t_vect v);
t_bool	is_inline(t_vect a, t_vect b, t_vect c);
t_bool	is_vinf(t_vect v);
t_bool	is_vrange(t_vect v, double min, double max);
t_bool	is_vsame(t_vect a, t_vect b);
t_bool	is_vzero(t_vect v);
t_vect	init_vect(double x, double y, double z);
t_vect	vadd(t_vect a, t_vect b);
t_vect	vcross(t_vect a, t_vect b);
t_vect	vdiv(t_vect v, double d);
t_vect	vscale(t_vect v, double s);
t_vect	vsub(t_vect a, t_vect b);
t_vect	vunit(t_vect v);
#endif
