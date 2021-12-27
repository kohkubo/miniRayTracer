/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 02:07:18 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 21:04:21 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_raytracing(t_raytracing *funcs)
{
	funcs[SP] = raytracing_sp;
	funcs[PL] = raytracing_pl;
	funcs[SQ] = raytracing_sq;
	funcs[CY] = raytracing_cy;
	funcs[TR] = raytracing_tr;
}

void	init_store_info(t_store_info *funcs)
{
	funcs[SP] = store_sp;
	funcs[PL] = store_pl;
	funcs[SQ] = store_sq;
	funcs[CY] = store_cy;
	funcs[TR] = store_tr;
	funcs[CAMERA] = store_camera;
	funcs[LIGHT] = store_light;
}

void	base_init(t_minirt *data, t_camera *cam)
{
	cam->base.bits_per_pixel = 100;
	cam->base.line_len = 100;
	cam->base.endian = 100;
	cam->base.img = mlx_new_image(data->mlx, data->scene.w, data->scene.h);
	cam->base.addr = mlx_get_data_addr(cam->base.img, &cam->base.bits_per_pixel,
										&cam->base.line_len, &cam->base.endian);
}

void	minirt_init(t_minirt *data)
{
	int x;
	int y;

	data->lights = NULL;
	data->cams = NULL;
	data->objs = NULL;
	data->ambl.range = -1;
	data->ambl.color[0] = 255;
	data->ambl.color[1] = 255;
	data->ambl.color[2] = 255;
	data->scene.color_bg = -1;
	data->bmp = 0;
	data->count = 0;
	data->cams_head = NULL;
	data->win = NULL;
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &x, &y);
	data->scene.w = x;
	data->scene.h = y;
	init_raytracing(data->raytracing);
}

void	scene_init(t_base *base, t_scene scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < scene.h)
	{
		x = 0;
		while (x < scene.w)
		{
			my_mlx_pixel_put(base, x, y, scene.color_bg);
			x++;
		}
		y++;
	}
}
