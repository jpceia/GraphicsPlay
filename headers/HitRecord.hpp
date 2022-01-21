/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HitRecord.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:54:14 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:21:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITRECORD_HPP
# define HITRECORD_HPP

# include "Vector.hpp"
# include "hittable/AHittable.hpp"

class AHittable;

/*
 * Raytracer (Core)
 */
struct HitRecord
{
	vec3f    p;
	vec3f    normal;
	vec3f    reflected;
    AHittable*              hittable;
	float                   t;
};

#endif
