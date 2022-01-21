/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:15:33 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:28:25 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Cylinder.hpp"
#include "miniRT.h"

// non copyable
Cylinder::Cylinder(const Cylinder& rhs) : AHittable(rhs.getName(), rhs.getMaterial()) {}
Cylinder& Cylinder::operator=(const Cylinder& rhs) { (void)rhs; return *this; }

Cylinder::Cylinder(const CylinderArgs& args) :
    AHittable("Cylinder", args.material),
    _base(args.base),
    _direction(args.direction),
    _radius(args.radius),
    _height(args.height)
{}

/*
 * Checks if a ray hits a cylinder
 * The equation of a cylinder is:
 * 	|(p - p0) x n)| = R
 * 	<p - p0, n> \in [0, height]
 * Substituting p by our ray r(t) = r0 + t * d, t > 0
 * We have a 2nd degree equation
 * R^2 = |(r0 - p0 + t * d) x n|^2 = |(r0 - p0) x n + (d x n) * t|^2
 *     = |d x n|^2 t^2 + 2 * t * <d x n, v x n> + |v x n|^2 
 * with v = r0 - p0
 * 
 * the coeficients of "a * t^2 + b * t + c = 0" are
 * a = |d x n|^2
 * b = 2 * <d x n, v x n>
 * c = |v x n|^2 - R^2
 * 
 * The solution is t = -h +- sqrt(h^2 - c)
 * with h = b / (2 * a)
 * 
 * Regarding the height of the cylinder, we still have
 * <r(t) - p0, n> = <d * t + v, n> = t * <d,n> + <v, n> between 0 and H
 * with v = r0 - p0
 */
bool Cylinder::hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
{
    vec3f v = r.getOrigin() - _base;
    vec3f d_cross_n = rt::cross(r.getDirection(), _direction);
    vec3f v_cross_n = rt::cross(v, _direction);
    Deg2eqParams params;
    params.a = d_cross_n.lengthSquared();
    params.b = 2 * rt::dot(d_cross_n, v_cross_n);
    params.c = v_cross_n.lengthSquared() - _radius * _radius;

    Range rng;
    if (!deg2eq_solve(params, &rng))
        return (false);
    if (rng.max < t_min || rng.min > t_max)
        return (false);
    float v_dot_n = rt::dot(v, _direction);
    float d_dot_n = rt::dot(r.getDirection(), _direction);
    float t = rng.max;
    bool is_tmin = false;
    if (rng.min >= t_min)
    {
        float h = v_dot_n + rng.min * d_dot_n;
        is_tmin = h >= 0 && h <= _height;
    }
    if (is_tmin)
        t = rng.min;
    else
    {
        float h = v_dot_n + t * d_dot_n;
        if (h < 0 || h > _height)
            return false;
    }
    rec.t = t;
    rec.p = r.getPointAt(rec.t);
    rec.normal = rec.p - _base;
    rec.normal -= _direction * rt::dot(rec.normal, _direction);
    rec.normal = rec.normal.normalize();
    return (true);
}