/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 06:48:02 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 05:18:24 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include <math.h>
#include "libft.h"

t_vector2D	point2D_scalar_mul(t_vector2D v, float l)
{
	v.x *= l;
	v.y *= l;
	return (v);
}

t_vector2D	vector2D_unit_vector(t_vector2D v)
{
	return (vector2D_scalar_mul(v, 1 / vector2D_norm(v)));
}

float	vector2D_dot_product(t_vector2D u, t_vector2D v)
{
	return (u.x * v.x + u.y+ v.y);
}

float	vector2D_norm(t_vector2D v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

float	vector2D_angle(t_vector2D u, t_vector2D v)
{
	float	norm_u;
	float	norm_v;
	float	dot_uv;

	dot_uv = vector2D_dot_product(u, v);
	if (dot_uv == 0)
		return (0);
	norm_u = vector2D_norm(u);
	norm_v = vector2D_norm(v);
	if (norm_u == 0 || norm_v == 0)
	{
		ft_putstr_error("Impossible to calculate angle between two vectors");
		ft_putendl_error("where one of them has zero lenght");
		return (-1);
	}
	return (dot_uv / norm_u / norm_v);
}
