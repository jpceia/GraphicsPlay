/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:05:31 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:31:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Sphere.hpp"

Sphere::Sphere(const SphereArgs& args) :
    AHittable("Sphere", args.material),
    _center(args.center),
    _radius(args.radius),
    _radius_sq(args.radius * args.radius)
{}

Sphere::Sphere(const Sphere& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _center(rhs._center),
    _radius(rhs._radius),
    _radius_sq(rhs._radius_sq)
{
}

Sphere& Sphere::operator=(const Sphere& rhs)
{
    (void)rhs;
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
bool Sphere::hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const
{
    vec3f v = ray.getOrigin() - _center;

    Deg2eqParams params;
    params.a = 1.0f;
    params.b = 2.0f * rt::dot(v, ray.getDirection());
    params.c = rt::dot(v, v) - _radius_sq;

    Range rng;
    if (!deg2eq_solve(params, &rng))
        return false;
    if (rng.min > t_rng.max || rng.max < t_rng.min)
        return false;
    if (rng.min >= t_rng.min)
        rec.t = rng.min;
    else if (rng.max <= t_rng.max)
        rec.t = rng.max;
    else
        return false;
    rec.p = ray.getPointAt(rec.t);
    rec.normal = (rec.p - _center).normalize();
    return (true);
}
