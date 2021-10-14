/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:00 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 21:28:59 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*
 * Checks if a ray hits a cylinder
 * The equation of a cylinder is:
 * 	|(p - p0) x n)| = R
 * 	<p - p0, n> \in [0, height]
 * Substituting p by our ray r(t) = r0 + t * d
 * We have a 2nd degree equation
 * R^2 = |(r0 - p0 + t * d) x n|^2 = |(r0 - p0) x n + (d x n) * t|^2
 *     = |d x n|^2 t^2 + 2 * t * <d x n, v x n> + |v x n|^2 
 * with v = r0 - p0
 * 
 * the coeficients of "a * t^2 + b * t + c = 0" are
 * a = |d x n|^2
 * b = 2 * <d x n, v x n>
 * c = |v x n|^2 - R^2
 * 
 * The solution is t = -h +- sqrt(h^2 - c)
 * with h = b / (2 * a)
 * 
 * Regarding the height of the cylinder, we still have
 * <r(t) - p0, n> = <d * t + v, n> = t * <d,n> + <v, n> between 0 and H
 * with v = r0 - p0
 */
t_bool	hit_cylinder(const t_ray3d *ray, const t_cylinder *cylinder,
		float t_min, t_hit_record *record)
{
	float	half_b;
	float	discriminant;
	t_vec3d	u;
	t_vec3d	v;
	t_vec3d	w;

	record->base_color = cylinder->color;
	u = vec3d_cross_product(ray->direction, cylinder->direction);
	v = vec3d_subtract(cylinder->p, ray->origin);
	w = vec3d_cross_product(v, cylinder->direction);
	half_b = vec3d_dot_product(u, w) / vec3d_norm_squared(u);
	discriminant = half_b * half_b;
	discriminant -= vec3d_norm_squared(w) - cylinder->radius * cylinder->radius;
	if (discriminant < 0)
		return (false);
	if (-half_b + sqrtf(discriminant) < t_min)
		return (false);
	if (-half_b - sqrtf(discriminant) < t_min)
		record->t = -half_b + sqrtf(discriminant);
	else
		record->t = -half_b - sqrtf(discriminant);
	record->p = ray3d_at(ray, record->t);
	record->n = vec3d_normalize(vec3d_subtract(record->p, cylinder->p));
	return (true);
}
