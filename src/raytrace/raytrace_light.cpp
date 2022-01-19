/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_light.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:02:28 by jceia             #+#    #+#             */
/*   Updated: 2022/01/19 00:12:22 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

float	get_diffuse_intensity(const rt::vector<float, 3>& v, const HitRecord& rec)
{
	return (std::max(v.dot(rec.normal) * rec.hittable->getMaterial().diffusion, 0.0f));
}

float	get_specular_intensity(const rt::vector<float, 3>& v, const HitRecord& rec)
{
	float	dot_prod = v.dot(rec.reflected);
	if (dot_prod < 0)
		return (0);
	return std::pow(dot_prod, rec.hittable->getMaterial().shininess) * rec.hittable->getMaterial().specular;
}

t_rgb	hit_light_contribution(
		const HitRecord &rec,
		const Light& light,
		const Scenario& scenario)
{
	HitRecord	hit_before_light;
	float		light_intensity;

	
	rt::Ray<float, 3>	ray_to_light = rt::Ray<float, 3>(rec.p, light.getOrigin() - rec.p);
	float dist = ray_to_light.getDirection().length();
	if (raytrace_hit(ray_to_light, scenario, 1e-3, hit_before_light))
		if (hit_before_light.t < dist)
			return (t_rgb());
	light_intensity = get_diffuse_intensity(ray_to_light.getDirection(), rec);
	light_intensity += get_specular_intensity(ray_to_light.getDirection(), rec);
	light_intensity *= light.getRatio();
	return (light.getColor() * light_intensity);
}

t_rgb	reflection_contribution(
	const HitRecord& rec,
	const Scenario& scenario,
	int n_reflections)
{
	t_rgb	color_shadow;
	rt::Ray<float, 3>	ray(rec.p, rec.reflected);
	color_shadow = raytrace_single(ray, scenario, n_reflections - 1);
	return (color_shadow * rec.hittable->getMaterial().mirror);
}

t_rgb	hit_color(
		const HitRecord& rec,
		const Scenario& scenario,
		int n_reflections)
{
	rt::vector<float, 3> color_shadow;
	AmbientLight amb = scenario.getAmbientLight();
	Material mat = rec.hittable->getMaterial();

	color_shadow = amb.color * mat.ambient * amb.ratio;
	for (std::list<Light>::const_iterator it = scenario.getLights().begin(); it != scenario.getLights().end(); ++it)
		color_shadow += hit_light_contribution(rec, *it, scenario);
	color_shadow = rt::elementwise_product(rec.color, color_shadow);
	if (n_reflections > 0)
		color_shadow += reflection_contribution(rec, scenario, n_reflections);
	return (color_shadow);
}
