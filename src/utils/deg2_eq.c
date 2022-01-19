/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deg2_eq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:17:29 by jceia             #+#    #+#             */
/*   Updated: 2022/01/18 06:01:34 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*
 * 2nd degree equations
 */

struct FloatPair
{
	float		min;
	float		max;
};

struct deg2EqCoefs
{
	float	a;
	float	b;
	float	c;
};


bool	deg2_eq_solutions(const deg2EqCoefs &params, FloatPair& t)
{
	float			tmp;

	tmp = params.b * params.b - 4 * params.a * params.c;
	if (tmp < 0)
		return (false);
	tmp = sqrtf(tmp);
	t.min = (-params.b - tmp) / (2 * params.a);
	t.max = (-params.b + tmp) / (2 * params.a);
	return (true);
}
