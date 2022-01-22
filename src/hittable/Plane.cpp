/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 02:56:52 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Plane.hpp"

Plane::Plane(const PlaneArgs& args) :
    AHittable("Plane", args.material),
    _point(args.point),
    _normal(args.normal)
{
}

// non copyable
Plane::Plane(const Plane& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _point(rhs._point),
    _normal(rhs._normal)
{
}

Plane& Plane::operator=(const Plane& rhs)
{
    if (this != &rhs)
    {
        _point = rhs._point;
        _normal = rhs._normal;
    }
    return *this;
}

/*
* Checks if a ray hits a plane
* Plane equation: < p - p0 , n > = 0
* Ray equation: r(t) = r0 + t * d, t > 0
* 
* Merging the two we get the following equation
*   <t * d + r0 - p0, n > = 0
* Equiv. to:
*   t = - <v,n> / <d,n>
* with v = r0 - p0
*/
bool Plane::hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const
{
    rec.normal = _normal;
    float dot_prod = rt::dot(r.getDirection(), _normal);
    if (dot_prod == 0)
        return (false);
    vec3f v = r.getOrigin() - _point;
    rec.t = -rt::dot(v, _normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return (false);
    rec.p = r.getPointAt(rec.t);
    return (true);
}
