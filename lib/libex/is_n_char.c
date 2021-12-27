/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_n_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:54:01 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/01 12:19:26 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"


t_bool		is_n_char(const char *s, int c, int max)
{
	uint8_t	dot;

	dot = 0;
	if (*s == c)
		return (TRUE);
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != c)
			return (TRUE);
		if (*s == c)
		{
			dot++;
			if (dot == max + 1)
				return (TRUE);
		}
		s++;
	}
	if (*(s - 1) == c)
		return (TRUE);
	return (FALSE);
}
