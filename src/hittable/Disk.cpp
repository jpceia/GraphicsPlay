/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:33:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Disk.hpp"

// non copyable
Disk::Disk(const Disk& rhs) : AHittable(rhs.getName(), rhs.getMaterial()) {}
Disk& Disk::operator=(const Disk& rhs) { (void)rhs; return *this; }

Disk::Disk(const DiskArgs& args) :
    AHittable("Disk", args.material),
    _center(args.center),
    _normal(args.normal),
    _radius(args.radius)
{}

bool Disk::hit(const Ray3f& r, float t_min, float t_max, HitRecord& rec) const
{
    rec.normal = _normal;
    float dot_prod = rt::dot(r.getDirection(), _normal);
    if (dot_prod == 0)
        return (false);
    vec3f v = r.getOrigin() - _center;
    rec.t = -rt::dot(v, _normal) / dot_prod;
    if (rec.t < t_min || rec.t > t_max)
        return (false);
    rec.p = r.getPointAt(rec.t);
    if ((_center - rec.p).lengthSquared() > _radius * _radius)
        return (false);
    return (true);
}