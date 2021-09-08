/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 06:48:02 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 05:17:57 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include <math.h>
#include "libft.h"

t_vector3D	point3D_scalar_mul(t_vector3D v, float l)
{
	v.x *= l;
	v.y *= l;
	v.z *= l;
	return (v);
}

t_vector3D	vector3D_unit_vector(t_vector3D v)
{
	return (vector3D_scalar_mul(v, 1 / vector3D_norm(v)));
}

float	vector3D_dot_product(t_vector3D u, t_vector3D v)
{
	return (u.x * v.x + u.y+ v.y + u.z * v.z);
}

float	vector3D_norm(t_vector3D v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float	vector3D_angle(t_vector3D u, t_vector3D v)
{
	float	norm_u;
	float	norm_v;
	float	dot_uv;

	dot_uv = vector3D_dot_product(u, v);
	if (dot_uv == 0)
		return (0);
	norm_u = vector3D_norm(u);
	norm_v = vector3D_norm(v);
	if (norm_u == 0 || norm_v == 0)
	{
		ft_putstr_error("Impossible to calculate angle between two vectors");
		ft_putendl_error("where one of them has zero lenght");
		return (-1);
	}
	return (dot_uv / norm_u / norm_v);
}
