/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:23:36 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 01:08:46 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef enum e_coord
{
	COORD_X,
	COORD_Y,
	COORD_Z
}	t_coord;

/*
 * vec3d
 */

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

t_vec3d	vec3d_create(float x, float y, float z);
t_vec3d	vec3d_origin(void);
t_vec3d	vec3d_subtract(t_vec3d q, t_vec3d p);
t_vec3d	vec3d_add(t_vec3d p, t_vec3d v);
float	vec3d_coord(t_vec3d p, t_coord coord);

t_vec3d	vec3d_scalar_mul(t_vec3d v, float l);
t_vec3d	vec3d_normalize(t_vec3d v);
t_vec3d	vec3d_cross_product(t_vec3d u, t_vec3d v);
t_vec3d	vec3d_elementwise_product(t_vec3d u, t_vec3d v);
t_vec3d	vec3d_interpolate(t_vec3d p, t_vec3d q, float t);

float	vec3d_dot_product(t_vec3d u, t_vec3d v);
float	vec3d_norm_squared(t_vec3d v);
float	vec3d_norm(t_vec3d v);
float	vec3d_angle(t_vec3d u, t_vec3d v);
t_vec3d	vec3d_clip(t_vec3d v, float a, float b);

#endif