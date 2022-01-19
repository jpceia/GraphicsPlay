/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:49 by jceia             #+#    #+#             */
/*   Updated: 2022/01/18 04:09:46 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	random_uniform()
{
	return (((float)rand()) / ((float)RAND_MAX));
}

rt::vector<float, 3>	vec3d_random()
{
	rt::vector<float, 3>	v;
	v[0] = random_uniform() - 1;
	v[1] = random_uniform() - 1;
	v[2] = random_uniform() - 1;
	return (v.normalize());
}
