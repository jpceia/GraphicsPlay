/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:10:31 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:24:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Plane.hpp"

Plane::Plane(const PlaneArgs& args) :
    APlaneSurface(
        "Plane",
        args.material,
        args.point,
        args.normal)
{
}

Plane::Plane(const Plane& rhs) :
    APlaneSurface(rhs)
{
}

bool Plane::_check_boundary(const vec3f& p) const
{
    (void)p;
    return true;
}
