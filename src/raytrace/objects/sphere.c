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
 * Sphere equation: || x - p_0 || = R
 * Ray equation: x = p + t * v, t > 0
 * 
 * Hence we have a 2nd degree equation
 * <v,v> t^2 + 2 <p-p0, v> t + <p-p0,p-p0> - R^2 = 0
 * 
 * In this case
 * a = <v,v> = 1 (direction in ray is unit vector)
 * h = <p-p0, v>
 * t = (-b +- sqrt(b*b-4*a*c) / (2 * a)) = -h +- sqrt(h*h - c)
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
