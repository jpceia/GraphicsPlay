/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 02:59:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Disk.hpp"


Disk::Disk(const DiskArgs& args) :
    AHittable("Disk", args.material),
    _center(args.center),
    _normal(args.normal),
    _radius(args.radius)
{
}

// non copyable
Disk::Disk(const Disk& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _center(rhs._center),
    _normal(rhs._normal),
    _radius(rhs._radius)
{
}

Disk& Disk::operator=(const Disk& rhs)
{
    if (this != &rhs)
    {
        _center = rhs._center;
        _normal = rhs._normal;
        _radius = rhs._radius;
    }
    return *this;
}


bool Disk::hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const
{
    rec.normal = _normal;
    float dot_prod = rt::dot(r.getDirection(), _normal);
    if (dot_prod == 0)
        return false;
    vec3f v = r.getOrigin() - _center;
    rec.t = -rt::dot(v, _normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return false;
    rec.p = r.getPointAt(rec.t);
    return (_center - rec.p).lengthSquared() <= _radius * _radius; // radius_2
}
