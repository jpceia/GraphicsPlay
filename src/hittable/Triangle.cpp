/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:53:08 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:33:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Triangle.hpp"

Triangle& Triangle::operator=(const Triangle& rhs) { (void)rhs; return *this; }

Triangle::Triangle(const TriangleArgs& args) :
    AHittable("Triangle", args.material)
{
    _vertex[0] = args.vertex[0];
    _vertex[1] = args.vertex[1];
    _vertex[2] = args.vertex[2];
}


Triangle::Triangle(const Triangle& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial())
{
    _vertex[0] = rhs._vertex[0];
    _vertex[1] = rhs._vertex[1];
    _vertex[2] = rhs._vertex[2];
}

bool Triangle::hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const
{
    vec3f u = _vertex[1] - _vertex[0];
    vec3f v = _vertex[2] - _vertex[0];
    rec.normal = rt::cross(u, v).normalize();
    float dot_prod = rt::dot(r.getDirection(), rec.normal);
    if (dot_prod == 0)
        return (false);
    vec3f w = r.getOrigin() - _vertex[0];
    rec.t = -rt::dot(w, rec.normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return (false);
    rec.p = r.getPointAt(rec.t);
    float x = rec.p.dot(u) / u.lengthSquared();
    float y = rec.p.dot(v) / v.lengthSquared();
    if (x < 0 || y < 0 || x + y > 1)
        return (false);
    return (true);
}
