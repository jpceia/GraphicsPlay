/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:05:31 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:21:43 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Sphere.hpp"

Sphere::Sphere(const SphereArgs& args) :
    AHittable("Sphere", args.material),
    _center(args.center),
    _radius(args.radius)
{}

Sphere::Sphere(const Sphere& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial())
{
}

Sphere& Sphere::operator=(const Sphere& rhs)
{
    _center = rhs._center;
    _radius = rhs._radius;
    return *this;
}

/*
* Checks if a ray hits a sphere
* Sphere equation: || p - p0 || = R
* Ray equation: r(t) = r0 + t * d, t > 0
* 
* Hence we have a 2nd degree equation
* <d,d> t^2 + 2 <r0 - p0, d> t + <r0 - p0, r0 - p0> - R^2 = 0
* 
* In this case
* a = <d,d> = 1 (direction in ray is an unit vector)
* v = r0 - p0
* h = <v, d>
* t = (-b +- sqrt(b*b-4*a*c) / (2 * a)) = -h +- sqrt(disc)
* disc = h * h - c
*/
bool Sphere::hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const
{
    vec3f v = r.getOrigin() - _center;
    float half_b = rt::dot(v, r.getDirection());
    float disc = half_b * half_b - rt::dot(v, v) + _radius * _radius;
    if (disc < 0)
        return (false);
    float sqrt_disc = sqrt(disc);
    if (-half_b + sqrt_disc < t_rng.min)
        return (false);
    if (-half_b - sqrt_disc < t_rng.min)
        rec.t = -half_b + sqrt_disc;
    else
        rec.t = -half_b - sqrt_disc;
    rec.p = r.getPointAt(rec.t);
    rec.normal = (rec.p - _center).normalize();
    return (true);
}