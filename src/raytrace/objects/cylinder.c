/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:00 by jceia             #+#    #+#             */
/*   Updated: 2021/10/09 07:05:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Checks if a ray hits a cylinder
 * The equation of a cylinder is:
 * 	|(p - p0) x n)| = R
 * 	<p - p0, n> \in [0, height]
 * Substituting p by our ray r(t) = p + t * v
 * We have
 * (p - p0 + t * v) x n = (p - p0) x n + (v x n) * t with norm R
 * to calculate the norm we need to use the inner product
 * |(p - p0) x n|^2 + 2 * <(p-p0) x n, v x n> t + |v x n|^2 * t^2 = R ^2
 */
t_bool	hit_cylinder(const t_ray3d *ray, const t_cylinder *cylinder,
		t_hit_record *record)
{
	/*
	float	a;
	float	h;
	float	c;
	float	t1, t2;
	t_vec3d	v;
	t_vec3d	v_n;
	t_vec3d d_n;

	record->base_color = cylinder->color;
	v = vec3d_subtract(ray->origin, cylinder->p);
	v_n = vec3d_cross_product(v, cylinder->n);
	d_n = vec3d_cross_product(ray->direction, cylinder->n);
	a = vec3d_norm_squared(d_n);
	h = vec3d_dot_product(v_n, d_n);
	c = vec3d_norm_squared(v_n);
	if (h * h - a * c < 0)
		return (false);
	t1 = (-h + sqrtf(h * h - a * c)) / a;
	t2 = (-h - sqrtf(h * h - a * c)) / a;
	//if(hit_cylinder_check_t(ray, cylinder, t));
	{
		shadow = false;

	}
	else
	{
		t = ...
		if (hit_color)
			shadow = false
	}
	// what is the right ?
	record->p = ray3d_at(ray, t1);
	v = vec3d_subtract(record->p, cylinder->p);
	v = vec3d_cross_product(v, cylinder->n);
	v = vec3d_cross_product(v, cylinder->n);
	record->n = vec3d_normalize(v);
	return (true);
	*/
	(void)ray;
	(void)cylinder;
	(void)record;
	return (false);
}
