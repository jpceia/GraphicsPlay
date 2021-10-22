/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/22 19:15:34 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
#include <math.h>

float	get_diffuse_intensity(const t_vec3d v, const t_hit_record *record)
{
	return (fmaxf(vec3d_dot_product(v, record->normal)
			* record->surf.k_diffusion, 0));
}

t_rgb	hit_light_contribution(
		const t_hit_record *hit_record,
		const t_light *light,
		const t_data *vars)
{
	float			dist;
	t_hit_record	hit_before_light;
	t_ray3d			ray_to_light;
	float			diffuse_intensity;

	ray_to_light = ray3d_from_two_points(hit_record->p, light->origin);
	dist = vec3d_norm(vec3d_subtract(light->origin, hit_record->p));
	if (raytrace_hit(&ray_to_light, vars, 1e-3, &hit_before_light))
		if (hit_before_light.t < dist)
			return (vec3d_origin());
	diffuse_intensity = get_diffuse_intensity(ray_to_light.direction, hit_record);
	diffuse_intensity *= light->ratio;
	return (vec3d_scalar_mul(light->color, diffuse_intensity));
}

t_rgb	hit_color(
		const t_hit_record *hit_record,
		const t_data *vars)
{
	t_vec3d			color_shadow;
	t_list			*lights;

	lights = vars->lights;
	color_shadow = vec3d_scalar_mul(
			vars->ambient.color, vars->ambient.ratio);
	while (lights)
	{
		color_shadow = vec3d_add(color_shadow,
				hit_light_contribution(
					hit_record, lights->content, vars));
		lights = lights->next;
	}
	return (vec3d_elementwise_product(hit_record->color, color_shadow));
}
