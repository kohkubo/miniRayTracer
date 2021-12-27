/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 01:30:59 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/04 21:11:39 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include "libex.h"
# include "libvect.h"
# include "enum.h"
# include "struct.h"
# include <math.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC 65307
# define KEY_A   97
# define KEY_S   115
# define KEY_Z   122
# define KEY_P   112
# define KEY_SP  32
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define CLIENT_MESSAGE 33
# define STRUCTURE_NOTIFY_MASK 0x20000L
# define KEY_PRESS 2
# define KEY_PRESS_MASK 0x1L
# define BUTTON_PRESS 4
# define BUTTON_PRESS_MASK 0x4L
# define MOTION_NOTIFY 6
# define POINTER_MOTION_MASK 0x40L
# define ERR "Error"
# define INVALID_ARG "Invalid argument"
# define INAPPRO_TYPE_OR_FORMAT "Inappropriate file type or format"
# define NOFILE_OR_DIR "No such file or directory"
# define ARG_ERROR "Argument error: "
# define FILE_ERROR "File error: "
# define PATH_ERROR "Path error: "
# define MALLOC_ERROR "Malloc error: "
# define VALUE_ERROR "Value error: "
# define TOO_MANY_ARG "Too many arguments"
# define BMP_HEADER_SIZE		14
# define BMP_INFO_HEADER_SIZE	40
# define BMP_FILE_NAME			"output.bmp"
# define EPSILON 0.00001
# define PI 3.1415926535
# define MIN_POS -9223372036854775808.0
# define MAX_POS  9223372036854775807.0
# define MIN_NOV -1.0
# define MAX_NOV 1.0
# define MIN_FOV 0
# define MAX_FOV 180
# define MIN_SIZE -9223372036854775808.0
# define MAX_SIZE  9223372036854775807.0
# define MIN_RGB 0
# define MAX_RGB 255
# ifdef __MACH__
#  define OS_NAME 1
# else
#  define OS_NAME 2
# endif
# ifdef __MACH__
#  define DESTROYNOTIFY 17
#  define MLX_DESTROY_DISPLAY
# else
#  define DESTROYNOTIFY 33
#  define MLX_DESTROY_DISPLAY mlx_destroy_display(data->mlx);
# endif
# define SAFE_FREE(p) {free(p); p = NULL;}
# define IS_INF(a) (a == INFINITY || a == -INFINITY)
# define IS_RANGE(n, a, b) (a <= n && n <= b)

int			get_depth(t_minirt *data, t_camera *cam, int x, int y);
int			set_depth(t_minirt *data, t_camera *cam, int x, int y);
int			create_trgb(int t, int r, int g, int b);
void		free_camera(t_minirt *data);
void		free_minirt(t_minirt *data);
t_status	store_sp(t_minirt *data, char **info);
t_status	store_sq(t_minirt *data, char **info);
t_status	store_pl(t_minirt *data, char **info);
t_status	store_cy(t_minirt *data, char **info);
t_status	store_tr(t_minirt *data, char **info);
void		init_raytracing(t_raytracing *funcs);
void		init_store_info(t_store_info *funcs);
void		base_init(t_minirt *data, t_camera *cam);
void		minirt_init(t_minirt *data);
void		scene_init(t_base *base, t_scene scene);
void		pixel_put(t_minirt *data, t_camera *c, int x, int y);
void		draw_scene(t_minirt *data, t_camera *cam);
t_status	store_info(t_minirt *data, char **info);
void		read_file(t_minirt *data);
int			main(int ac, char **av);
double		solution(double a, double b, double c, double t[2]);
double		raytracing_cy_sub(t_objs *obj, t_vect p[2], double t[2], t_vect at[2]);
double		raytracing_cy(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2]);
void		unique_square(t_vect n, t_vect center[2]);
double		ft_atof(const char *s);
t_vect		ato_vect(char *s);
t_status	store_color(char *s, double color[3]);
t_objs_id	objs_id(char **info);
void		error_end(t_minirt *data, char *s);
void		validate_args(t_minirt *data, int ac, char **av);
t_status	parse_line(t_minirt *data, char *line);
t_status	buf_init(t_minirt *data, t_camera *cam);
void		init_window(t_minirt *data);
void		vect_light(t_light *light, t_camera *cam);
void		objs_reflection(t_objs *objs, t_light *light);
void		objs_color(t_minirt *data, t_objs *objs);
void		shadowing(t_minirt *data, t_objs *objs, t_light *light, t_camera *cam);
void		lighting(t_minirt *data, t_objs *objs, t_camera *cam);
t_status	store_scene(char **info, t_scene *scene);
t_status	store_ambl(char **info, t_ambl *ambl);
t_status	store_light(t_minirt *data, char **info);
t_status	store_camera(t_minirt *data, char **info);
t_status	store_mat(char *s, t_mat *mat);
void		bmp_make(t_minirt *data);
double		raytracing_sp(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2]);
double		raytracing_tr(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2]);
double		raytracing_pl(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2]);
double		raytracing_sq(t_objs *obj, t_vect s, t_vect sn, t_vect lookat[2]);
void		camera_on(t_minirt *data);
int			window_exposed(t_minirt *data);
int			close_program(t_minirt *data);
void		minirt_mlx_loop(t_minirt *data);
void		my_mlx_pixel_put(t_base *base, int x, int y, int color);
int			key_press(int keycode, t_minirt *data);

#endif
