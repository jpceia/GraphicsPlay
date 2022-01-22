/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:49 by jceia             #+#    #+#             */
/*   Updated: 2022/01/22 03:37:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.hpp"

float	random_uniform()
{
	return (((float)rand()) / ((float)RAND_MAX));
}

vec3f	vec3d_random()
{
	vec3f	v;
	v[0] = random_uniform() - 1;
	v[1] = random_uniform() - 1;
	v[2] = random_uniform() - 1;
	return (v.normalize());
}
