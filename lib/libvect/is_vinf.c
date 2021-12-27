/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_vinf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:11:10 by kohkubo           #+#    #+#             */
/*   Updated: 2021/02/26 20:29:33 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

static t_bool is_inf(double a)
{
	return (a == INFINITY || a == -INFINITY);
}

t_bool	is_vinf(t_vect v)
{
	return (is_inf(v.x) || is_inf(v.y) || is_inf(v.z));
}
