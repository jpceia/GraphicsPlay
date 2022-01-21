/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:19:10 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Disk.hpp"

// non copyable
Disk::Disk(const Disk& rhs) : AHittable(rhs.getName(), rhs.getMaterial()) {}
Disk& Disk::operator=(const Disk& rhs) { (void)rhs; return *this; }

Disk::Disk(const DiskArgs& args) :
    AHittable("Disk", args.material),
    center(args.p),
    n(args.direction),
    radius(args.radius)
{}

bool Disk::hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
{
    rec.normal = this->n;
    float dot_prod = rt::dot(r.getDirection(), this->n);
    if (dot_prod == 0)
        return (false);
    rt::vector<float, 3> v = r.getOrigin() - this->center;
    rec.t = -rt::dot(v, this->n) / dot_prod;
    if (rec.t < t_min || rec.t > t_max)
        return (false);
    rec.p = r.getPointAt(rec.t);
    if ((this->center - rec.p).lengthSquared() > this->radius * this->radius)
        return (false);
    return (true);
}