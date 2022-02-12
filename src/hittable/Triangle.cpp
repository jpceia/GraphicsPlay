/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:53:08 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:31:56 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Triangle.hpp"

static vec3f covector(const vec3f& v)
{
    return v / v.lengthSquared();
}

Triangle::Triangle(const TriangleArgs& args) :
    APlaneSurface(
        "Triangle",
        args.material,
        args.vertex[0],
        rt::cross(
            args.vertex[1] - args.vertex[0],
            args.vertex[2] - args.vertex[0]
        ).normalize()),
    _coedge1(covector(args.vertex[1] - args.vertex[0])),
    _coedge2(covector(args.vertex[2] - args.vertex[0]))
{
}

Triangle::Triangle(const Triangle& rhs) :
    APlaneSurface(rhs),
    _coedge1(rhs._coedge1),
    _coedge2(rhs._coedge2)
{
}

bool Triangle::_check_boundary(const vec3f& p) const
{
    vec3f v = p - _base;
    float x = v.dot(_coedge1);
    float y = v.dot(_coedge2);
    return !(x < 0 || y < 0 || x + y > 1);
}
