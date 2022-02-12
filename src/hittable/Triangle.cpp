/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:53:08 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:24:43 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Triangle.hpp"

vec3f covector(const vec3f& v)
{
    return v / v.lengthSquared();
}

Triangle& Triangle::operator=(const Triangle& rhs) { (void)rhs; return *this; }

Triangle::Triangle(const TriangleArgs& args) :
    AHittable("Triangle", args.material),
    _base(args.vertex[0]),
    _coedge1(covector(args.vertex[1] - args.vertex[0])),
    _coedge2(covector(args.vertex[2] - args.vertex[0])),
    _normal(rt::cross(_coedge1, _coedge2).normalize())
{
}


Triangle::Triangle(const Triangle& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _base(rhs._base),
    _coedge1(rhs._coedge1),
    _coedge2(rhs._coedge2),
    _normal(rhs._normal)
{
}

bool Triangle::hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const
{
    float dot_prod = rt::dot(ray.getDirection(), _normal);
    if (dot_prod == 0)
        return false;
    rec.t = -rt::dot(ray.getOrigin() - _base, _normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return false;
    rec.p = ray.getPointAt(rec.t);
    vec3f p = rec.p - _base;
    float x = p.dot(_coedge1);
    float y = p.dot(_coedge2);
    if (x < 0 || y < 0 || x + y > 1)
        return false;
    rec.normal = _normal;
    return true;
}
