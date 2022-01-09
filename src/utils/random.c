/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:49 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:02:02 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	random_uniform(void)
{
	return (((float)rand()) / ((float)RAND_MAX));
}

t_vec3d	vec3d_random(void)
{
	return (vec3d_normalize(vec3d_create(
				random_uniform() - 1,
				random_uniform() - 1,
				random_uniform() - 1)));
}
