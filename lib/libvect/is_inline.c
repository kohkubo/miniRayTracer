/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_inline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:43:46 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/03 16:11:32 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

t_bool	is_inline(t_vect a, t_vect b, t_vect c)
{
	return (is_vzero(vcross(vsub(a, b), vsub(a, c))));
}
