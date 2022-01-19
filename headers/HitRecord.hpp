/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HitRecord.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:54:14 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 00:15:31 by jpceia           ###   ########.fr       */
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
	rt::vector<float, 3>    p;
	rt::vector<float, 3>    normal;
	rt::vector<float, 3>    reflected;
    AHittable*              hittable;
	rt::vector<float, 3>    color;
	float                   t;

	HitRecord() :
		t(1000000.0f)
	{
	}
};

#endif
