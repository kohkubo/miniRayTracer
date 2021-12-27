/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:53:31 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 16:07:01 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include "libft.h"
# include "libex.h"
# include "libvect.h"
# include "enum.h"

typedef unsigned char	t_pix;

typedef struct		s_base
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_base;

typedef struct		s_scene
{
	double			w;
	double			h;
	int				color_bg;
}					t_scene;

typedef struct		s_buf
{
	int				w;
	int				h;
	double			*pixel;
}					t_buf;

typedef struct		s_mat
{
	double			diff[3];
	double			spec[3];
	double			high;
}					t_mat;

typedef struct		s_ambl
{
	double			range;
	double			color[3];
}					t_ambl;

typedef struct		s_light
{
	t_vect			p;
	t_vect			n;
	double			range;
	double			color[3];
	double			cos1;
	double			cos2;
	double			cosf;
	struct s_light	*next;
	t_vect			lookat_to_light_unit;
	t_vect			lookat_to_light;
	double			lightlen;
}					t_light;

typedef struct		s_camera
{
	t_vect			p;
	t_vect			n;
	double			fov;
	t_base			base;
	t_vect			lookat[2];
	t_vect			view;
	t_vect			scene_center;
	double			focal_len;
	t_buf			*buf;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_objs
{
	t_objs_id		id;
	int				num;
	t_vect			p1;
	t_vect			p2;
	t_vect			p3;
	t_vect			n;
	double			rad;
	double			half_size;
	double			height;
	t_mat			mat;
	double			shade[3];
	double			t[2];
	t_vect			at;
	t_vect			normal;
	struct s_objs	*next;
}					t_objs;

typedef double	(*t_raytracing)(t_objs *obj, t_vect s,
t_vect sn, t_vect lookat[2]);

typedef struct		s_minirt
{
	t_scene			scene;
	t_ambl			ambl;
	t_objs			*objs;
	t_light			*lights;
	t_camera		*cams;
	t_camera		*cams_head;
	double			depth;
	double			depth_tmp;
	void			*win;
	int				count;
	char			path[2048];
	t_raytracing	raytracing[5];
	int				color;
	int				fd;
	u_int8_t		bmp;
	void			*mlx;
}					t_minirt;

typedef t_status	(*t_store_info)(t_minirt *data, char **info);

typedef struct		s_bmp_header
{
	u_int8_t		bf_type[2];
	u_int32_t		bf_size;
	u_int16_t		bf_reserved1;
	u_int16_t		bf_reserved2;
	u_int32_t		bf_off_bits;
	u_int32_t		bi_size;
	u_int32_t		bi_width;
	u_int32_t		bi_height;
	u_int32_t		bi_planes;
	u_int32_t		bi_bit_count;
}					t_bmp_header;

#endif
