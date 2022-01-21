/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:53:08 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:24:32 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Triangle.hpp"

Triangle& Triangle::operator=(const Triangle& rhs) { (void)rhs; return *this; }

Triangle::Triangle(const TriangleArgs& args) :
    AHittable("Triangle", args.material),
    p1(args.p1),
    p2(args.p2),
    p3(args.p3)
{}


Triangle::Triangle(const Triangle& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    p1(rhs.p1),
    p2(rhs.p2),
    p3(rhs.p3)
{
}

bool Triangle::hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
{
    rt::vector<float, 3> u = this->p2 - this->p1;
    rt::vector<float, 3> v = this->p3 - this->p1;
    rec.normal = rt::cross(u, v).normalize();
    float dot_prod = rt::dot(r.getDirection(), rec.normal);
    if (dot_prod == 0)
        return (false);
    rt::vector<float, 3> w = r.getOrigin() - this->p1;
    rec.t = -rt::dot(w, rec.normal) / dot_prod;
    if (rec.t < t_min || rec.t > t_max)
        return (false);
    rec.p = r.getPointAt(rec.t);
    float x = rec.p.dot(u) / u.lengthSquared();
    float y = rec.p.dot(v) / v.lengthSquared();
    if (x < 0 || y < 0 || x + y > 1)
        return (false);
    return (true);
}
