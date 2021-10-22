/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/22 13:10:17 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
					raytrace_pixel(i, j, N_ANTIALIAS, vars);
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
		if (vec3d_dot_product(ray->direction, record->normal) > 0)
			record->normal = vec3d_scalar_mul(record->normal, -1);
		record->reflected = ray3d_reflected(ray, record->normal).direction;
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const t_ray3d *primary_ray, const t_data *vars)
{
	t_hit_record	hit_record;

	if (raytrace_hit(primary_ray, vars, 0, &hit_record))
		return (hit_color(&hit_record, vars));
	return (vars->ambient.color);
}
