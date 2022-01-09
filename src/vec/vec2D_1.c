/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2D_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 22:32:05 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:13:49 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vec.h"
#include "libft.h"

t_vec2d	vec2d_create(float x, float y)
{
	t_vec2d	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vec2d	vec2d_origin(void)
{
	return (vec2d_create(0.0, 0.0));
}

t_vec2d	vec2d_subtract(t_vec2d q, t_vec2d p)
{
	q.x -= p.x;
	q.y -= p.y;
	return (q);
}

t_vec2d	vec2d_add(t_vec2d p, t_vec2d v)
{
	p.x += v.x;
	p.y += v.y;
	return (p);
}

float	vec2d_coord(t_vec2d p, t_coord coord)
{
	if (coord == COORD_X)
		return (p.x);
	if (coord == COORD_Y)
		return (p.y);
	fprintf(stderr, "Invalid coordinate\n");
	return (0.0);
}
