/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 16:09:29 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_rgb	hit_color(const t_hit_record *hit_record, const t_scenario *scenario)
{
	/*
	t_light			*light;
	t_vec3D			direction_to_light;
	float			distance_to_light;
	t_hit_record	hit_before_light;
	t_ray3D			ray_to_light;
	t_bool			shadow;

	light = (t_light *)(scenario->lights->content);
	direction_to_light = vec3D_subtract(light->origin, hit_record->p);
	distance_to_light = vec3D_norm(direction_to_light);
	ray_to_light = ray3D_from_two_points(hit_record->p, light->origin);
	shadow = false;
	if (raytrace_hit(&ray_to_light, scenario, &hit_before_light))
		if (hit_before_light.t < distance_to_light)
			shadow = true;
	float a;
	if (shadow)
		a = 1 - light->ratio;
	else
		a = 1 - (1 - vec3D_dot_product(ray_to_light.direction, hit_record->n)) * light->ratio ;
		return (hit_record->base_color);
	return (vec3D_scalar_mul(hit_record->base_color, a));
	*/
	return (hit_record->base_color);
}

/*
 * Checks if a ray hits a sphere
 * Sphere equation: || x - p_0 || = R
 * Ray equation: x = p + t * direction, t > 0
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
t_bool	hit_sphere(const t_ray3D *ray, const t_sphere *sphere,
		t_hit_record *record)
{
	float	h;
	float	c;
	t_vec3D	v;
	float	disc;

	record->base_color = sphere->color;
	v = vec3D_subtract(ray->origin, sphere->center);
	h = vec3D_dot_product(v, ray->direction);
	c = vec3D_norm_squared(v) - sphere->radius * sphere->radius;
	disc = h * h - c;
	if (disc < 0)
		return (false);
	if (-h + sqrtf(disc) < 0)
		return (false);
	if (-h - sqrtf(disc) < 0)
		record->t = -h + sqrtf(disc);
	else
		record->t = -h - sqrtf(disc);
	record->p = ray3D_at(ray, record->t);
	record->n = vec3D_normalize(vec3D_subtract(record->p, sphere->center));
	return (true);
}

t_bool	hit_plane(const t_ray3D *ray, const t_plane *plane, t_hit_record *record)
{
	t_vec3D	v;
	float	dot_prod;

	record->base_color = plane->color;
	record->n = plane->n;
	dot_prod = vec3D_dot_product(plane->n, ray->direction);
	if (dot_prod == 0)
		return (false);
	v = vec3D_subtract(ray->origin, plane->p);
	record->t = vec3D_dot_product(v, plane->n) / dot_prod; // check signal
	if (record->t < 0)
		return (false);
	record->p = ray3D_at(ray, record->t);
	return (true);
}

t_bool	hit_cylinder(const t_ray3D *ray, const t_cylinder *cylinder,
		t_hit_record *record)
{
	(void)ray;
	(void)cylinder;
	(void)record;
	return (false);
}

t_bool	hit_object(const t_ray3D *ray, t_object *obj, t_hit_record *record)
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
