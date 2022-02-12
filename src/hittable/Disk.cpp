/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:36:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Disk.hpp"


Disk::Disk(const DiskArgs& args) :
    AHittable("Disk", args.material),
    _center(args.center),
    _normal(args.normal),
    _radius(args.radius),
    _radius_sq(args.radius * args.radius)
{
}

// non copyable
Disk::Disk(const Disk& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _center(rhs._center),
    _normal(rhs._normal),
    _radius(rhs._radius),
    _radius_sq(rhs._radius_sq)
{
}

Disk& Disk::operator=(const Disk& rhs)
{
    (void)rhs;
    return *this;
}


bool Disk::hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const
{
    rec.normal = _normal;
    float dot_prod = rt::dot(ray.getDirection(), _normal);
    if (dot_prod == 0)
        return false;
    vec3f v = ray.getOrigin() - _center;
    rec.t = -rt::dot(v, _normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return false;
    rec.p = ray.getPointAt(rec.t);
    return (_center - rec.p).lengthSquared() <= _radius_sq;
}
