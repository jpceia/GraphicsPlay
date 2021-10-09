/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 06:42:25 by jceia             #+#    #+#             */
/*   Updated: 2021/10/09 07:02:33 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	record->t = vec3d_dot_product(v, plane->n) / dot_prod; // check signal
	if (record->t < 0)
		return (false);
	record->p = ray3d_at(ray, record->t);
	return (true);
}
