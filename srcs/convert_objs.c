/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:11:28 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 17:09:12 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_status	store_sp(t_minirt *data, char **info)
{
	t_objs		*objs;
	t_status	flg;

	if (!is_n_split(info, 4))
		return (ERROR);
	if (!(objs = malloc(sizeof(t_objs))))
		return (ERROR);
	objs->id = SP;
	objs->num = data->count++;
	objs->p1 = ato_vect(info[SP_POS]);
	objs->rad = ft_atof(info[SP_DIAMETER]) / 2;
	flg = store_mat(info[SP_RGB], &(objs->mat));
	objs->next = NULL;
	if (data->objs)
		objs->next = data->objs;
	data->objs = objs;
	if (flg == ERROR || IS_INF(objs->rad) || is_vinf(objs->p1) ||
														objs->rad <= EPSILON)
		return (ERROR);
	return (SUCCESS);
}

t_status	store_sq(t_minirt *data, char **info)
{
	t_objs		*objs;
	t_status	flg;

	if (!is_n_split(info, 5))
		return (ERROR);
	if (!(objs = malloc(sizeof(t_objs))))
		return (ERROR);
	objs->id = SQ;
	objs->num = data->count++;
	objs->p1 = ato_vect(info[SQ_POS]);
	objs->n = ato_vect(info[SQ_NOV]);
	if (is_vrange(objs->n, -1.0, 1.0) && !is_vzero(objs->n))
		objs->n = vunit(objs->n);
	else
		objs->n = VERROR;
	objs->half_size = ft_atof(info[SQ_SIDESIZE]) / 2;
	flg = store_mat(info[SQ_RGB], &(objs->mat));
	objs->next = NULL;
	if (data->objs)
		objs->next = data->objs;
	data->objs = objs;
	if (flg == ERROR || IS_INF(objs->half_size) || is_vinf(objs->p1)
							|| is_vinf(objs->n) || objs->half_size <= EPSILON)
		return (ERROR);
	return (SUCCESS);
}

t_status	store_pl(t_minirt *data, char **info)
{
	t_objs		*objs;
	t_status	flg;

	if (!is_n_split(info, 4))
		return (ERROR);
	if (!(objs = malloc(sizeof(t_objs))))
		return (ERROR);
	objs->id = PL;
	objs->num = data->count++;
	objs->p1 = ato_vect(info[PL_POS]);
	objs->n = ato_vect(info[PL_NOV]);
	if (is_vrange(objs->n, -1.0, 1.0) && !is_vzero(objs->n))
		objs->n = vunit(objs->n);
	else
		objs->n = VERROR;
	flg = store_mat(info[PL_RGB], &(objs->mat));
	objs->next = NULL;
	if (data->objs)
		objs->next = data->objs;
	data->objs = objs;
	if (flg == ERROR || is_vinf(objs->p1) || is_vinf(objs->n))
		return (ERROR);
	return (SUCCESS);
}

t_status	store_cy(t_minirt *data, char **info)
{
	t_objs		*objs;
	t_status	flg;

	if (!is_n_split(info, 6) || !(objs = malloc(sizeof(t_objs))))
		return (ERROR);
	objs->id = CY;
	objs->num = data->count++;
	objs->p1 = ato_vect(info[CY_POS]);
	objs->n = ato_vect(info[CY_NOV]);
	if (is_vrange(objs->n, -1.0, 1.0) && !is_vzero(objs->n))
		objs->n = vunit(objs->n);
	else
		objs->n = VERROR;
	objs->rad = ft_atof(info[CY_DIAMETER]) / 2;
	objs->height = ft_atof(info[CY_HEIGHT]);
	flg = store_mat(info[CY_RGB], &(objs->mat));
	objs->next = NULL;
	if (data->objs)
		objs->next = data->objs;
	data->objs = objs;
	if (flg == ERROR || IS_INF(objs->rad) || IS_INF(objs->height) ||
		is_vinf(objs->p1) || is_vinf(objs->n) || objs->rad <= EPSILON ||
													objs->height <= EPSILON)
		return (ERROR);
	return (SUCCESS);
}

t_status	store_tr(t_minirt *data, char **info)
{
	t_objs		*objs;
	t_status	flg;

	if (!is_n_split(info, 5))
		return (ERROR);
	if (!(objs = malloc(sizeof(t_objs))))
		return (ERROR);
	objs->id = TR;
	objs->num = data->count++;
	objs->p1 = ato_vect(info[TR_POS1]);
	objs->p2 = ato_vect(info[TR_POS2]);
	objs->p3 = ato_vect(info[TR_POS3]);
	flg = store_mat(info[TR_RGB], &(objs->mat));
	objs->next = NULL;
	if (data->objs)
		objs->next = data->objs;
	data->objs = objs;
	if (flg == ERROR || is_vinf(objs->p1) || is_vinf(objs->p2) ||
				is_vinf(objs->p3) || is_inline(objs->p1, objs->p2, objs->p3))
		return (ERROR);
	return (SUCCESS);
}
