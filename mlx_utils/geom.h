/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 22:50:23 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 10:59:26 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOM_H
# define GEOM_H

# include "color.h"

/*
 * 2D Structures
 */
typedef struct s_point2D
{
	float	x;
	float	y;
}	t_point2D;

typedef t_point2D	t_vector2D;

typedef struct s_ray2D
{
	t_point2D	origin;
	t_vector2D	direction;
}	t_ray2D;

typedef struct s_line2D
{
	t_point2D	p;
	t_point2D	q;
}	t_line2D;

t_point2D	point2D_create(float x, float y);
t_vector2D	point2D_subtract(t_point2D a, t_point2D b);
t_point2D	point2D_add(t_point2D a, t_vector2D v);

t_vector2D	vector2D_scalar_mul(t_vector2D v, float l);
t_vector2D	vector2D_unit_vector(t_vector2D v);
float	vector2D_dot_product(t_vector2D u, t_vector2D v);
float	vector2D_norm(t_vector2D v);
float	vector2D_angle(t_vector2D u, t_vector2D v);

/*
 * 3D Structures
 */
typedef struct s_point3D
{
	float	x;
	float	y;
	float	z;
}	t_point3D;

typedef t_point3D	t_vector3D;

typedef struct s_ray3D
{
	t_point3D	origin;
	t_vector3D	direction;
}	t_ray3D;

typedef struct s_line3D
{
	t_point3D	p;
	t_point3D	q;
}	t_line3D;

t_point3D	point3D_create(float x, float y, float z);
t_vector3D	point3D_subtract(t_point3D a, t_point3D b);
t_point3D	point3D_add(t_point3D a, t_vector3D v);

t_vector3D	vector3D_scalar_mul(t_vector3D v, float l);
t_vector3D	vector3D_unit_vector(t_vector3D v);
float	vector3D_dot_product(t_vector3D u, t_vector3D v);
float	vector3D_norm(t_vector3D v);
float	vector3D_angle(t_vector3D u, t_vector3D v);

/*
 * Projections 3D -> 2D
 */
// t_point2D   proj_isometric(t_point3D p);

#endif