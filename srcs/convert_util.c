/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:10:54 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 19:12:28 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ft_atof(const char *s)
{
	int8_t	neg;
	size_t	i;
	double	frac;
	double	nb;

	neg = 1;
	if (*s == '-')
		neg = *s++ == '-' ? -1 : 1;
	if (is_n_char(s, '.', 1) || !*s)
		return (INFINITY);
	nb = 0.0;
	while (ft_isdigit(*s))
		nb = nb * 10 + *s++ - '0';
	if (nb == INFINITY || !*s)
		return (nb * neg);
	frac = 0;
	i = ft_strlen(s + 1);
	if (6 < i)
		return (INFINITY);
	while (ft_isdigit(s[i]) && 0 < i)
		frac = frac / 10 + (s[i--] - '0') / 10.0;
	return ((nb + frac) * neg);
}

t_vect		ato_vect(char *s)
{
	char	**ss;
	t_vect	vect;

	if (!is_n_split((ss = ft_split(s, ',')), 3))
	{
		free_ss(&ss);
		return (VERROR);
	}
	vect = init_vect(ft_atof(ss[X]), ft_atof(ss[Y]), ft_atof(ss[Z]));
	free_ss(&ss);
	return (vect);
}

t_status	store_color(char *s, double color[3])
{
	char	**ss;

	if (is_n_char(s, ',', 2))
		return (ERROR);
	if (!is_n_split((ss = ft_split(s, ',')), 3))
	{
		free_ss(&ss);
		return (ERROR);
	}
	color[R] = ft_atof(ss[R]) / 255;
	color[G] = ft_atof(ss[G]) / 255;
	color[B] = ft_atof(ss[B]) / 255;
	free_ss(&ss);
	if (!is_ranges(color, 0.0, 1.0))
		return (ERROR);
	return (SUCCESS);
}

t_objs_id	objs_id(char **info)
{
	if (!ft_strcmp(info[0], "sp"))
		return (SP);
	else if (!ft_strcmp(info[0], "sq"))
		return (SQ);
	else if (!ft_strcmp(info[0], "pl"))
		return (PL);
	else if (!ft_strcmp(info[0], "cy"))
		return (CY);
	else if (!ft_strcmp(info[0], "tr"))
		return (TR);
	else if (!ft_strcmp(info[0], "c"))
		return (CAMERA);
	else if (!ft_strcmp(info[0], "l"))
		return (LIGHT);
	else
		return (UNKNOWN);
}
