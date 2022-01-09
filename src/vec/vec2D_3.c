/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2D_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:39:38 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:13:57 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "vec.h"

float	vec2d_norm_squared(t_vec2d v)
{
	return (v.x * v.x + v.y * v.y);
}

float	vec2d_norm(t_vec2d v)
{
	return (sqrtf(vec2d_norm_squared(v)));
}

float	vec2d_angle(t_vec2d u, t_vec2d v)
{
	float	norm_u;
	float	norm_v;
	float	dot_uv;

	dot_uv = vec2d_dot_product(u, v);
	norm_u = vec2d_norm(u);
	norm_v = vec2d_norm(v);
	if (norm_u == 0 || norm_v == 0)
	{
		fprintf(stderr, "Vector with zero length\n");
		return (0);
	}
	return (dot_uv / norm_u / norm_v);
}

t_vec2d	vec2d_elementwise_product(t_vec2d u, t_vec2d v)
{
	u.x *= v.x;
	u.y *= v.y;
	return (u);
}

t_vec2d	vec2d_clip(t_vec2d v, float a, float b)
{
	v.x = fminf(fmaxf(v.x, a), b);
	v.y = fminf(fmaxf(v.y, a), b);
	return (v);
}
