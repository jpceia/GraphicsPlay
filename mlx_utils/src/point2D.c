/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 22:27:46 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 05:29:14 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

t_point2D	point2D_create(float x, float y)
{
	t_point2D	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vector2D	point2D_subtract(t_point2D p, t_point2D q)
{
	p.x -= q.x;
	p.y -= q.y;
	return (p);
}

t_point2D	point2D_add(t_point2D p, t_vector2D v)
{
	p.x += v.x;
	p.y += v.y;
	return (p);
}
