/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 22:32:05 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:13:43 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vec.h"
#include "libft.h"

t_vec3d	vec3d_create(float x, float y, float z)
{
	t_vec3d	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vec3d	vec3d_origin(void)
{
	return (vec3d_create(0.0, 0.0, 0.0));
}

t_vec3d	vec3d_subtract(t_vec3d q, t_vec3d p)
{
	q.x -= p.x;
	q.y -= p.y;
	q.z -= p.z;
	return (q);
}

t_vec3d	vec3d_add(t_vec3d p, t_vec3d v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return (p);
}

float	vec3d_coord(t_vec3d p, t_coord coord)
{
	if (coord == COORD_X)
		return (p.x);
	if (coord == COORD_Y)
		return (p.y);
	if (coord == COORD_Z)
		return (p.z);
	fprintf(stderr, "Invalid coordinate\n");
	return (0.0);
}
