/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 09:05:52 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/01 22:54:12 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

static int		ft_cmp(char a, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (a == str[i])
			return (1);
		i++;
	}
	return (0);
}

static int		arraylen(char *str, char *charset)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	i = 0;
	j = ft_strlen(str);
	while (str[i] && i <= j)
	{
		if (!ft_cmp(str[i], charset))
		{
			len++;
			while (!ft_cmp(str[i], charset) && str[i])
				i++;
			if (!str[i])
				break ;
		}
		i++;
	}
	return (len);
}

char			**ft_split_charset(char *str, char *charset)
{
	char	**array;
	size_t	i;
	size_t	j;
	int		head;

	i = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (arraylen(str, charset) + 1))))
		return (NULL);
	head = 0;
	while (str[i])
	{
		if (!ft_cmp(str[i], charset))
		{
			j = i;
			while (!ft_cmp(str[i], charset) && str[i])
				i++;
			if (i != j)
				array[head++] = ft_strndup(&str[j], i - j);
			if (!str[i])
				break ;
		}
		i++;
	}
	array[head] = 0;
	return (array);
}
