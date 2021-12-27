/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:30:08 by kohkubo           #+#    #+#             */
/*   Updated: 2021/01/19 00:33:14 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libex.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t	i;
	char	*copy;

	if (!(copy = (char *)malloc(n + 1)))
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
