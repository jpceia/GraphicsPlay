/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:00 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 16:45:31 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <math.h>

float	hit_cone_dist(const t_ray3d *ray, const t_cone *cone,
		float min_dist, t_float_pair *t_pair)
{
	float	t;
	float	v_dot_n;
	float	d_dot_n;
	float	h;
	t_vec3d	v;

	t = t_pair->max;
	if (t < min_dist)
		return (-1);
	v = vec3d_subtract(ray->origin, cone->p);
	v_dot_n = vec3d_dot_product(v, cone->direction);
	d_dot_n = vec3d_dot_product(ray->direction, cone->direction);
	if (t_pair->min >= min_dist)
	{
		h = v_dot_n + t_pair->min * d_dot_n;
		if (h >= 0 && h <= cone->height)
			t = t_pair->min;
	}
	if (t != t_pair->min)
	{
		h = v_dot_n + t * d_dot_n;
		if (h < 0 || h > cone->height)
			return (-1);
	}
	return (t);
}

/*
 * Normal vector to cone
 * https://math.stackexchange.com/questions/3349384/
 * normal-vector-of-a-cone-pointing-outward
 */
void	hit_cone_fill_record(const t_ray3d *ray, const t_cone *cone,
		t_hit_record *record)
{
	t_vec3d	v;

	record->base_color = cone->color;
	record->p = ray3d_at(ray, record->t);
	v = vec3d_subtract(record->p, cone->p);
	record->n = vec3d_add(v, vec3d_scalar_mul(cone->direction,
				vec3d_dot_product(v, cone->direction)
				* (pow(cone->radius / cone->height, 2) - 1)));
	record->n = vec3d_normalize(record->n);
}

void	update_cone_eq_params(const t_ray3d *ray, const t_cone *cone,
		t_deg2_eq_coefs *params)
{
	t_vec3d			v;
	t_vec3d			d_cross_n;
	t_vec3d			v_cross_n;
	float			v_dot_n;
	float			d_dot_n;

	v = vec3d_subtract(ray->origin, cone->p);
	d_cross_n = vec3d_cross_product(ray->direction, cone->direction);
	v_cross_n = vec3d_cross_product(v, cone->direction);
	v_dot_n = vec3d_dot_product(v, cone->direction);
	d_dot_n = vec3d_dot_product(ray->direction, cone->direction);
	params->a = vec3d_norm_squared(d_cross_n);
	params->a -= powf(d_dot_n * cone->radius / cone->height, 2);
	params->b = 2 * vec3d_dot_product(d_cross_n, v_cross_n);
	params->b += 2 * d_dot_n * (cone->height - v_dot_n)
		* powf(cone->radius / cone->height, 2);
	params->c = vec3d_norm_squared(v_cross_n);
	params->c -= powf(cone->height - v_dot_n, 2)
		* powf(cone->radius / cone->height, 2);
}

/*
 * Checks if a ray hits a cone
 * The equation of a cone is:
 * 	|(p - p0) x n)| = R * (1 - <p-p0, n> / H)
 * 	<p - p0, n> \in [0, height]
 * Substituting p by our ray r(t) = r0 + t * d, t > 0
 * We have a 2nd degree equation "a * t^2 + b * t + c = 0" 
 * with coeficients
 * a = |d x n|^2 - (R/H * <d,n>)^2
 * b = 2 * <d x n, v x n> + 2 * <d,n> * (H - <v,n>) * (R/H)^2
 * c = |v x n|^2 - (R - <v,n>/H)^2
 * where v = r0 - p0
 * 
 * The solution is t = -h +- sqrt(h^2 - c)
 * with h = b / (2 * a)
 * 
 * Regarding the height of the cone, we still have
 * <r(t) - p0, n> = <d * t + v, n> = t * <d,n> + <v, n> between 0 and H
 * with v = r0 - p0
 */
t_bool	hit_cone(const t_ray3d *ray, const t_cone *cone,
		float t_min, t_hit_record *record)
{
	t_float_pair	t_pair;
	t_deg2_eq_coefs	params;

	update_cone_eq_params(ray, cone, &params);
	if (!deg2_eq_solutions(&params, &t_pair))
		return (false);
	record->t = hit_cone_dist(ray, cone, t_min, &t_pair);
	if (record->t < 0)
		return (false);
	hit_cone_fill_record(ray, cone, record);
	return (true);
}
