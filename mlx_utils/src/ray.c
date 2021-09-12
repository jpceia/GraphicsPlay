/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:35:16 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 13:10:36 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_ray3D	ray3D_from_two_points(t_vec3D p, t_vec3D q)
{
	t_ray3D	r;

	r.origin = p;
	r.direction = vec3D_normalize(vec3D_subtract(q, p));
	return (r);
}

t_vec3D	ray3D_at(const t_ray3D *ray, float t)
{
	return (vec3D_add(ray->origin, vec3D_scalar_mul(ray->direction, t)));
}