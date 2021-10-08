/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 05:58:14 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_rgb	hit_light_contribution(const t_hit_record *hit_record,
		const t_light *light, const t_data *vars)
{
	t_vec3d			direction_to_light;
	t_hit_record	hit_before_light;
	t_ray3d			ray_to_light;
	float			distance_to_light;
	float			light_intensity;

	direction_to_light = vec3d_subtract(light->origin, hit_record->p);
	distance_to_light = vec3d_norm(direction_to_light);
	ray_to_light = ray3d_from_two_points(hit_record->p, light->origin);
	if (raytrace_hit(&ray_to_light, vars, &hit_before_light))
		if (hit_before_light.t < distance_to_light)
			return (vec3d_origin());
	light_intensity = vec3d_dot_product(
			ray_to_light.direction, hit_record->n) * light->ratio;
	if (light_intensity < 0)
		light_intensity = 0;
	return (vec3d_scalar_mul(light->color, light_intensity));
}

t_rgb	hit_color(const t_hit_record *hit_record, const t_data *vars)
{
	t_vec3d			color_shadow;
	t_list			*lights;

	lights = vars->lights;
	color_shadow = vec3d_scalar_mul(
			vars->ambient.color, vars->ambient.ratio);
	while (lights)
	{
		color_shadow = vec3d_add(color_shadow,
				hit_light_contribution(hit_record, lights->content, vars));
		lights = lights->next;
	}
	return (vec3d_elementwise_product(hit_record->base_color, color_shadow));
	return (hit_record->base_color);
}

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

t_bool	hit_plane(const t_ray3d *ray, const t_plane *plane,
		t_hit_record *record)
{
	t_vec3d	v;
	float	dot_prod;

	record->base_color = plane->color;
	record->n = plane->n;
	dot_prod = vec3d_dot_product(plane->n, ray->direction);
	if (dot_prod == 0)
		return (false);
	v = vec3d_subtract(ray->origin, plane->p);
	record->t = -vec3d_dot_product(v, plane->n) / dot_prod; // check signal
	if (record->t < 0)
		return (false);
	record->p = ray3d_at(ray, record->t);
	return (true);
}

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

t_bool	hit_object(const t_ray3d *ray, t_object *obj, t_hit_record *record)
{
	record->obj = obj;
	if (obj->obj_type == SPHERE)
		return (hit_sphere(ray, obj->data, record));
	if (obj->obj_type == PLANE)
		return (hit_plane(ray, obj->data, record));
	if (obj->obj_type == CYLINDER)
		return (hit_cylinder(ray, obj->data, record));
	exit (EXIT_FAILURE);
}
