/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vcross.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:32:20 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 11:32:22 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

t_vect	vcross(t_vect a, t_vect b)
{
	t_vect v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}