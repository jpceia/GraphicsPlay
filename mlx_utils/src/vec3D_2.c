/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:27:22 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 12:34:41 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx_utils.h"

t_vec3D	vec3D_scalar_mul(t_vec3D v, float l)
{
	v.x *= l;
	v.y *= l;
	v.z *= l;
	return (v);
}

t_vec3D	vec3D_normalize(t_vec3D v)
{
	return (vec3D_scalar_mul(v, 1 / vec3D_norm(v)));
}

float	vec3D_dot_product(t_vec3D u, t_vec3D v)
{
	return (u.x * v.x + u.y+ v.y + u.z * v.z);
}

t_vec3D	vec3D_cross_product(t_vec3D u, t_vec3D v)
{
	t_vec3D	w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.z;
	return (w);
}

t_vec3D	vec3D_interpolate(t_vec3D p, t_vec3D q, float t)
{
	t_vec3D	r;

	r.x = t * q.x + (1 - t) * p.x;
	r.y = t * q.y + (1 - t) * p.y;
	r.z = t * q.z + (1 - t) * p.z;
	return (r);
}