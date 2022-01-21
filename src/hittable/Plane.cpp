/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:19:15 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Plane.hpp"

Plane::Plane(const PlaneArgs& args) :
    AHittable("Plane", args.material),
    p(args.p),
    n(args.normal)
{}

// non copyable
Plane::Plane(const Plane& rhs) : AHittable(rhs.getName(), rhs.getMaterial()) {}
Plane& Plane::operator=(const Plane& rhs) { (void)rhs; return *this; }

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
bool Plane::hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
{
    rec.normal = this->n;
    float dot_prod = rt::dot(r.getDirection(), this->n);
    if (dot_prod == 0)
        return (false);
    rt::vector<float, 3> v = r.getOrigin() - this->p;
    rec.t = -rt::dot(v, this->n) / dot_prod;
    if (rec.t < t_min || rec.t > t_max)
        return (false);
    rec.p = r.getPointAt(rec.t);
    return (true);
}
