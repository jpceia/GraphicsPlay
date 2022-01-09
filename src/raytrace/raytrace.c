/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:40:49 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	raytrace_scenario(t_data *vars)
{
	int			i;
	int			j;

	i = 0;
	while (i < vars->camera->pixels_height)
	{
		j = 0;
		while (j < vars->camera->pixels_width)
		{
			vars->buf[i * vars->camera->pixels_width + j] = \
					raytrace_pixel(i, j, vars->n_antialias, vars);
			j++;
		}
		i++;
	}
}

t_bool	raytrace_hit(const t_ray3d *ray, const t_data *vars,
		float t_min, t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	hit_rec;
	t_list			*objs;

	objs = vars->objects;
	hit_anything = false;
	while (objs)
	{
		if (hit_object(ray, objs->content, t_min, &hit_rec))
		{
			if (!hit_anything || record->t > hit_rec.t)
				ft_memcpy(record, &hit_rec, sizeof(t_hit_record));
			hit_anything = true;
		}
		objs = objs->next;
	}
	if (hit_anything)
	{
		record->normal = vec3d_normalize(vec3d_add(record->normal,
					vec3d_scalar_mul(vec3d_random(), record->surf.k_wrinkle)));
		if (vec3d_dot_product(ray->direction, record->normal) > 0)
			record->normal = vec3d_scalar_mul(record->normal, -1);
		record->reflected = ray3d_reflected(ray, record->normal).direction;
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const t_ray3d *primary_ray,
		const t_data *vars, int n_reflections)
{
	t_hit_record	record;

	if (raytrace_hit(primary_ray, vars, 1e-2, &record))
		return (hit_color(&record, vars, n_reflections));
	return (vars->ambient.color);
}
