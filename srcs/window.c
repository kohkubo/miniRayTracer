/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:41:38 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 20:54:08 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		window_exposed(t_minirt *data)
{
	if (data->cams)
		mlx_put_image_to_window(data->mlx, data->win,
												data->cams->base.img, 0, 0);
	return (1);
}

int		close_program(t_minirt *data)
{
	free_minirt(data);
	exit(EXIT_SUCCESS);
	return (1);
}

void	minirt_mlx_loop(t_minirt *data)
{
	data->win = mlx_new_window(data->mlx,
									data->scene.w, data->scene.h, data->path);
	mlx_hook(data->win, DESTROYNOTIFY, 1 << 17, close_program, data);
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 1, key_press, data);
	mlx_hook(data->win, 12, 1L << 15, window_exposed, data);
	if (data->cams)
		mlx_put_image_to_window(data->mlx, data->win,
												data->cams->base.img, 0, 0);
	mlx_loop(data->mlx);
}

void	my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
	char	*dst;

	dst = base->addr + (y * base->line_len + x * (base->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		key_press(int keycode, t_minirt *data)
{
	if (keycode == KEY_ESC)
	{
		close_program(data);
	}
	if (keycode == KEY_A)
	{
		if (data->cams->next)
			data->cams = data->cams->next;
		else
			data->cams = data->cams_head;
		mlx_put_image_to_window(data->mlx, data->win,
													data->cams->base.img, 0, 0);
	}
	return (0);
}
