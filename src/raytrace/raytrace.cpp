/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2022/01/19 00:13:46 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	raytrace_scenario(Scenario& scenario)
{
	for (int i = 0; i < scenario.getScreenHeight(); ++i)
		for (int j = 0; j < scenario.getScreenWidth(); ++j)
			scenario.setPixel(i, j, raytrace_pixel(i, j, 1, scenario));
}

bool	raytrace_hit(
	const rt::Ray<float, 3> &ray,
	const Scenario &scenario,
	float t_min,
	HitRecord& rec)
{
	bool		hit_anything = false;
	HitRecord	hit_rec;

	for (std::list<AHittable *>::const_iterator it = scenario.getHittables().begin();
		it != scenario.getHittables().end();
		++it)
	{
		AHittable *hittable = *it;
		if (hittable->hit(ray, t_min, 10000.0f, hit_rec))
		{
			hit_anything = true;
			hit_rec.hittable = hittable;
			if (hit_rec.t < rec.t)
				rec = hit_rec;
		}
	}
	if (hit_anything)
	{
		//rec.normal = (vec3d_random() * rec.hittable->getMaterial().wrinkle).normalize();
		if (rt::dot(ray.getDirection(), rec.normal) > 0)
			rec.normal *= -1; // -v is invalid ??
		rec.reflected = ray.reflected(rec.normal);
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const rt::Ray<float, 3>& primary_ray,
	const Scenario& scenario, int n_reflections)
{
	HitRecord	rec;
	
	if (raytrace_hit(primary_ray, scenario, 1e-2, rec))
		return (hit_color(rec, scenario, n_reflections));
	return (scenario.getAmbientLight().color);
}
