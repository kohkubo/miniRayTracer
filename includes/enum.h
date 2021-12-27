/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:17:59 by kohkubo           #+#    #+#             */
/*   Updated: 2021/03/02 09:18:00 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum		e_coordinates
{
	X,
	Y,
	Z
}					t_coordinates;

typedef enum		e_rgb
{
	R,
	G,
	B
}					t_rgb;

typedef enum		e_status
{
	ERROR,
	SUCCESS
}					t_status;

typedef enum		e_vc
{
	N,
	P
}					t_vc;

typedef enum		e_type
{
	POS,
	NOV,
	FOV,
	SIZE,
}					t_type;

typedef enum		e_resolution
{
	RESOLU_ID,
	RESOLU_X,
	RESOLU_Y
}					t_resolution;

typedef enum		e_amlb_info
{
	AMBL_ID,
	AMBL_RANGE,
	AMBL_RGB
}					t_ambl_info;

typedef enum		e_light_info
{
	LIGHT_ID,
	LIGHT_POS,
	LIGHT_RANGE,
	LIGHT_RGB
}					t_light_info;

typedef enum		e_camera_info
{
	CAMERA_ID,
	CAMERA_POS,
	CAMERA_NOV,
	CAMERA_FOV
}					t_camera_info;

typedef enum		e_sp_info
{
	SP_ID,
	SP_POS,
	SP_DIAMETER,
	SP_RGB
}					t_sp_info;

typedef	enum		e_pl_info
{
	PL_ID,
	PL_POS,
	PL_NOV,
	PL_RGB
}					t_pl_info;

typedef enum		e_sq_info
{
	SQ_ID,
	SQ_POS,
	SQ_NOV,
	SQ_SIDESIZE,
	SQ_RGB
}					t_sq_info;

typedef enum		e_cy_info
{
	CY_ID,
	CY_POS,
	CY_NOV,
	CY_DIAMETER,
	CY_HEIGHT,
	CY_RGB
}					t_cy_info;

typedef enum		e_tr_info
{
	TR_ID,
	TR_POS1,
	TR_POS2,
	TR_POS3,
	TR_RGB
}					t_tr_info;

typedef enum		e_objs_id
{
	SP,
	PL,
	SQ,
	CY,
	TR,
	CAMERA,
	LIGHT,
	UNKNOWN
}					t_objs_id;

#endif
