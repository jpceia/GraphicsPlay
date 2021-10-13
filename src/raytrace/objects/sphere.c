/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:43:03 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:23:14 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*
 * Checks if a ray hits a sphere
 * Sphere equation: || p - p0 || = R
 * Ray equation: r(t) = r0 + t * d, t > 0
 * 
 * Hence we have a 2nd degree equation
 * <d,d> t^2 + 2 <r0 - p0, d> t + <r0 - p0, r0 - p0> - R^2 = 0
 * 
 * In this case
 * a = <d,d> = 1 (direction in ray is an unit vector)
 * v = r0 - p0
 * h = <v, d>
 * t = (-b +- sqrt(b*b-4*a*c) / (2 * a)) = -h +- sqrt(disc)
 * disc = h * h - c
 */
t_bool	hit_sphere(const t_ray3d *ray, const t_sphere *sphere,
		t_hit_record *record)
{
	float	h;
	float	c;
	t_vec3d	v;
	float	disc;

	record->base_color = sphere->color;
	v = vec3d_subtract(ray->origin, sphere->center);
	h = vec3d_dot_product(v, ray->direction);
	c = vec3d_norm_squared(v) - sphere->radius * sphere->radius;
	disc = h * h - c;
	if (disc < 0)
		return (false);
	if (-h + sqrtf(disc) < 0)
		return (false);
	if (-h - sqrtf(disc) < 0)
		record->t = -h + sqrtf(disc);
	else
		record->t = -h - sqrtf(disc);
	record->p = ray3d_at(ray, record->t);
	record->n = vec3d_normalize(vec3d_subtract(record->p, sphere->center));
	return (true);
}
