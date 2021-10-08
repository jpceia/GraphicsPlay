/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:00:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 05:58:24 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	raytrace_scenario(const t_data *vars)
{
	t_camera	*cam;
	t_vec3d		v_yz;
	t_ray3d		ray;
	int			i;
	int			j;

	cam = (t_camera *)(vars->cameras->content);
	i = 0;
	while (i < cam->pixels_height)
	{
		v_yz = vec3d_add(
				cam->direction,
				vec3d_scalar_mul(
					cam->basis_y,
					cam->view_height * ((i + 0.5) / cam->pixels_height - 0.5)));
		j = 0;
		while (j < cam->pixels_width)
		{
			ray = ray3d_from_two_points(
					cam->origin,
					vec3d_add(
						v_yz,
						vec3d_scalar_mul(
							cam->basis_x,
							cam->view_width * ((j + 0.5) / cam->pixels_width - 0.5)
						)));
			vars->buf[i * cam->pixels_width + j] = raytrace_single(&ray, vars);
			j++;
		}
		i++;
	}
}

void	hit_record_copy(t_hit_record *hr1, t_hit_record *hr2)
{
	hr1->base_color = hr2->base_color;
	hr1->n = hr2->n;
	hr1->obj = hr2->obj;
	hr1->p = hr2->p;
	hr1->t = hr2->t;
}

t_bool	raytrace_hit(const t_ray3d *ray, const t_data *vars,
		t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	hit_rec;
	t_list			*objs;

	objs = vars->objects;
	hit_anything = false;
	while (objs)
	{
		if (hit_object(ray, objs->content, &hit_rec))
		{
			if (!hit_anything || record->t > hit_rec.t)
				hit_record_copy(record, &hit_rec);
			hit_anything = true;
		}
		objs = objs->next;
	}
	return (hit_anything);
}

t_rgb	raytrace_single(const t_ray3d *ray, const t_data *vars)
{
	t_hit_record	hit_record;

	if (raytrace_hit(ray, vars, &hit_record))
		return (hit_color(&hit_record, vars));
	return (vars->ambient.color);
}
