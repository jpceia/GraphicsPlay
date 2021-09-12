/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3D_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:27:30 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 12:39:11 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "libft.h"

t_vec3D	vec3D_create(float x, float y, float z)
{
	t_vec3D	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vec3D	vec3D_origin(void)
{
	return (vec3D_create(0.0, 0.0, 0.0));
}

t_vec3D	vec3D_subtract(t_vec3D q, t_vec3D p)
{
	q.x -= p.x;
	q.y -= p.y;
	q.z -= p.z;
	return (q);
}

t_vec3D	vec3D_add(t_vec3D p, t_vec3D v)
{
	p.x += v.x;
	p.y += v.y;
	p.z += v.z;
	return (p);
}

float	vec3D_coord(t_vec3D p, t_coord coord)
{
	switch (coord)
	{
	case COORD_X:
		return (p.x);
	case COORD_Y:
		return (p.y);
	case COORD_Z:
		return (p.z);
	}
	ft_putendl_error("Invalid coordinate");
	return (0.0);
}
