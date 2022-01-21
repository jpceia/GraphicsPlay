/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HitRecord.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 00:54:14 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 10:59:40 by jpceia           ###   ########.fr       */
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
	float                   t;
};

#endif
