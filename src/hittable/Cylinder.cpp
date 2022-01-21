/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:15:33 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:19:04 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Cylinder.hpp"

// non copyable
Cylinder::Cylinder(const Cylinder& rhs) : AHittable(rhs.getName(), rhs.getMaterial()) {}
Cylinder& Cylinder::operator=(const Cylinder& rhs) { (void)rhs; return *this; }

Cylinder::Cylinder(const CylinderArgs& args) :
    AHittable("Cylinder", args.material),
    p(args.p),
    direction(args.direction),
    radius(args.radius),
    height(args.height)
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
    rt::vector<float, 3> v = r.getOrigin() - this->p;
    rt::vector<float, 3> d_cross_n = rt::cross(r.getDirection(), this->direction);
    rt::vector<float, 3> v_cross_n = rt::cross(v, this->direction);
    float a = d_cross_n.lengthSquared();
    float b = 2 * rt::dot(d_cross_n, v_cross_n);
    float c = v_cross_n.lengthSquared() - this->radius * this->radius;

    float   disc = b * b - 4 * a * c;
    if (disc < 0)
        return (false);
    float sqrt_disc = std::sqrt(disc);
    float t1 = (-b - sqrt_disc) / (2 * a);
    float t2 = (-b + sqrt_disc) / (2 * a);
    if (t2 < t_min || t1 > t_max)
        return (false);
    float v_dot_n = rt::dot(v, this->direction);
    float d_dot_n = rt::dot(r.getDirection(), this->direction);
    float t = -1.0;
    if (t1 >= t_min)
    {
        float h = v_dot_n + t1 * d_dot_n;
        if (h >= 0 && h <= this->height)
            t = t1;
    }
    if (t != t_min)
    {
        float h = v_dot_n + t * d_dot_n;
        if (h < 0 || h > this->height)
            return false;
    }
    if (t < 0)
        return (false);
    rec.t = t;
    rec.p = r.getPointAt(rec.t);
    rec.normal = rec.p - this->p;
    rec.normal -= this->direction * rt::dot(rec.normal, this->direction);
    rec.normal = rec.normal.normalize();
    return (true);
}