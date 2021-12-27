/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_vrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:52:43 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 11:37:35 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

static t_bool	is_range(double n, double min, double max)
{
	return (min <= n && n <= max);
}

t_bool	is_vrange(t_vect v, double min, double max)
{
	return (is_range(v.x, min, max) && is_range(v.y, min, max) &&
													is_range(v.z, min, max));
}
