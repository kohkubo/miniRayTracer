/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ranges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:07:46 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 11:38:46 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

t_bool	is_ranges(double array[3], double a, double b)
{
	return (IS_RANGE(array[0], a, b) &&
						IS_RANGE(array[1], a, b) && IS_RANGE(array[2], a, b));
}
