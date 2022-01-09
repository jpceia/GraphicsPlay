/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:41:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

float	get_diffuse_intensity(const t_vec3d v, const t_hit_record *record)
{
	return (fmaxf(vec3d_dot_product(v, record->normal)
			* record->surf.k_diffusion, 0));
}

float	get_specular_intensity(const t_vec3d v, const t_hit_record *record)
{
	float	dot_prod;

	dot_prod = vec3d_dot_product(v, record->reflected);
	if (dot_prod < 0)
		return (0);
	return (pow(dot_prod, record->surf.shininess) * record->surf.k_specular);
}

t_rgb	hit_light_contribution(
		const t_hit_record *record,
		const t_light *light,
		const t_data *vars)
{
	float			dist;
	t_hit_record	hit_before_light;
	t_ray3d			ray_to_light;
	float			light_intensity;

	ray_to_light = ray3d_from_two_points(record->p, light->origin);
	dist = vec3d_norm(vec3d_subtract(light->origin, record->p));
	if (raytrace_hit(&ray_to_light, vars, 1e-3, &hit_before_light))
		if (hit_before_light.t < dist)
			return (vec3d_origin());
	light_intensity = get_diffuse_intensity(ray_to_light.direction, record);
	light_intensity += get_specular_intensity(ray_to_light.direction, record);
	light_intensity *= light->ratio;
	return (vec3d_scalar_mul(light->color, light_intensity));
}

t_rgb	reflection_contribution(
	const t_hit_record *record,
	const t_data *vars,
	int n_reflections)
{
	t_rgb	color_shadow;
	t_ray3d	ray;

	ray = ray3d_create(record->p, record->reflected);
	color_shadow = raytrace_single(&ray, vars, n_reflections - 1);
	return (vec3d_scalar_mul(color_shadow, record->surf.k_mirror));
}

t_rgb	hit_color(
		const t_hit_record *record,
		const t_data *vars,
		int n_reflections)
{
	t_vec3d			color_shadow;
	t_list			*lights;

	lights = vars->lights;
	color_shadow = vec3d_scalar_mul(
			vars->ambient.color, record->surf.k_ambient * vars->ambient.ratio);
	while (lights)
	{
		color_shadow = vec3d_add(color_shadow, hit_light_contribution(
					record, lights->content, vars));
		lights = lights->next;
	}
	color_shadow = vec3d_elementwise_product(record->color, color_shadow);
	if (n_reflections > 0)
		color_shadow = vec3d_add(color_shadow,
				reflection_contribution(record, vars, n_reflections));
	return (color_shadow);
}
