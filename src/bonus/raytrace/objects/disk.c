/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:02:22 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 20:59:53 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_bool	hit_disk(const t_ray3d *ray, const t_disk *disk,
		float t_min, t_hit_record *record)
{
	t_vec3d	v;
	float	r2;
	float	dot_prod;

	record->n = disk->n;
	dot_prod = vec3d_dot_product(disk->n, ray->direction);
	if (dot_prod == 0)
		return (false);
	v = vec3d_subtract(ray->origin, disk->center);
	record->t = -vec3d_dot_product(v, disk->n) / dot_prod;
	if (record->t < t_min)
		return (false);
	record->p = ray3d_at(ray, record->t);
	r2 = disk->radius * disk->radius;
	if (vec3d_norm_squared(vec3d_subtract(disk->center, record->p)) <= r2)
		return (true);
	return (false);
}
