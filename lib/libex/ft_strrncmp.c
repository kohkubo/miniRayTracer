/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:24:53 by kohkubo           #+#    #+#             */
/*   Updated: 2021/02/22 13:57:31 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"


int		ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)s1 + ft_strlen(s1);
	u2 = (unsigned char *)s2 + ft_strlen(s2);
	while (0 < n--)
	{
		u1--;
		u2--;
		if ((*u1 != *u2))
			return (u1 - u2);
	}
	return (0);
}
