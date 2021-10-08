/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:35:16 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 02:24:39 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray3d	ray3d_from_two_points(t_vec3d p, t_vec3d q)
{
	t_ray3d	r;

	r.origin = p;
	r.direction = vec3d_normalize(vec3d_subtract(q, p));
	return (r);
}

t_vec3d	ray3d_at(const t_ray3d *ray, float t)
{
	return (vec3d_add(ray->origin, vec3d_scalar_mul(ray->direction, t)));
}
