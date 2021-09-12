/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 15:08:51 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	raytrace_scenario(const t_scenario *scenario, t_rgb *buf)
{
	t_camera	*cam;
	t_vec3D		v_yz;
	t_ray3D		ray;
	int			i;
	int			j;

	cam = (t_camera *)(scenario->cameras->content);
	i = 0;
	while (i < cam->pixels_height)
	{
		v_yz = vec3D_add(
				cam->direction,
				vec3D_scalar_mul(
					cam->basis_y,
					cam->view_height * ((i + 0.5) / cam->pixels_height - 0.5)
				)
		);
		j = 0;
		while (j < cam->pixels_height)
		{
			ray = ray3D_from_two_points(
				cam->origin,
				vec3D_add(
					v_yz,
					vec3D_scalar_mul(
						cam->basis_x,
						cam->view_width * ((j + 0.5) / cam->pixels_width - 0.5)
					)
				)
			);
			buf[i * cam->pixels_width + j] = raytrace_single_ray(&ray, scenario);
			j++;
		}
		i++;
	}
}

t_rgb	raytrace_single_ray(const t_ray3D *ray, const t_scenario *scenario)
{
	t_bool			hit_anything;
	t_hit_record	closest_hit_rec;
	t_hit_record	hit_rec;
	t_list			*objs;

	objs = scenario->objects;
	hit_anything = false;
	while (objs)
	{
		if (hit_object(ray, objs->content, &hit_rec))
		{
			if (!hit_anything || closest_hit_rec.t > hit_rec.t)
				closest_hit_rec = hit_rec;
			hit_anything = true;
		}
		objs = objs->next;
	}
	if (hit_anything)
		return (hit_color(&closest_hit_rec, scenario));
	return (scenario->ambient.color);
}
