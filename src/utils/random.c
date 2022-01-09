/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:49 by jceia             #+#    #+#             */
/*   Updated: 2021/10/22 23:03:02 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

float	random_uniform(void)
{
	return (((float)rand()) / RAND_MAX);
}

t_vec3d	vec3d_random(void)
{
	return (vec3d_normalize(vec3d_create(
				random_uniform() - 1,
				random_uniform() - 1,
				random_uniform() - 1)));
}
