/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 00:13:26 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 19:51:01 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bmp_header	init_header(t_minirt *data)
{
	u_int32_t		size;
	u_int32_t		off_bits;
	t_bmp_header	header;

	off_bits = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
	size = off_bits + data->scene.w * data->scene.h * 4;
	header.bf_type[0] = 'B';
	header.bf_type[1] = 'M';
	header.bf_size = size;
	header.bf_reserved1 = 0;
	header.bf_reserved2 = 0;
	header.bf_off_bits = off_bits;
	header.bi_size = 40;
	header.bi_width = (int32_t)data->scene.w;
	header.bi_height = (int32_t)data->scene.h;
	header.bi_planes = 1;
	header.bi_bit_count = 32;
	return (header);
}

static void			write_header(t_minirt *data, int fd)
{
	t_bmp_header	header;
	int				i;

	i = 0;
	header = init_header(data);
	write(fd, "BM", 2);
	write(fd, &header.bf_size, 4);
	write(fd, &header.bf_reserved1, 2);
	write(fd, &header.bf_reserved2, 2);
	write(fd, &header.bf_off_bits, 4);
	write(fd, &header.bi_size, 4);
	write(fd, &header.bi_width, 4);
	write(fd, &header.bi_height, 4);
	write(fd, &header.bi_planes, 2);
	write(fd, &header.bi_bit_count, 2);
	while (i++ < 24)
		write(fd, "\0", 1);
}

static void			write_scene(t_minirt *data, t_camera *cam, int fd)
{
	int			x;
	int			y;
	int			color;
	int			*p;

	y = 0;
	while (y < data->scene.h)
	{
		x = 0;
		while (x < data->scene.w)
		{
			p = (int *)(cam->base.addr + (((int)data->scene.h - y - 1) *
					cam->base.line_len) + x * (cam->base.bits_per_pixel / 8));
			color = *p;
			write(fd, &color, 4);
			x++;
		}
		y++;
	}
}

static t_status		save_bmp(t_minirt *data, t_camera *cam, char *nb)
{
	int			fd;
	char		path[255];

	ft_strlcpy(path, "./bmp/minirt", SIZE_MAX);
	ft_strlcat(path, nb, SIZE_MAX);
	ft_strlcat(path, ".bmp", SIZE_MAX);
	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		return (ERROR);
	write_header(data, fd);
	write_scene(data, cam, fd);
	close(fd);
	return (SUCCESS);
}

void				bmp_make(t_minirt *data)
{
	t_camera	*cam;
	char		nb[255];

	nb[0] = '0';
	nb[1] = '\0';
	cam = data->cams;
	while (cam)
	{
		buf_init(data, cam);
		base_init(data, cam);
		scene_init(&cam->base, data->scene);
		draw_scene(data, cam);
		if (save_bmp(data, cam, nb) == ERROR)
			error_end(data, "error bmp");
		nb[0]++;
		cam = cam->next;
	}
	free_minirt(data);
}
