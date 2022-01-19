/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:39 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/18 05:54:30 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_HPP
# define SPHERE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct SphereArgs
{
    rt::vector<float, 3>	center;
    float					radius;
    Material                material;
};

class Sphere : public AHittable
{
private:
    rt::vector<float, 3> center;
    float radius;

    // non copyable
    Sphere(const Sphere& rhs) : AHittable(rhs.getMaterial()) {}
    Sphere& operator=(const Sphere& rhs) { (void)rhs; return *this; }

public:
    Sphere(const SphereArgs& args) :
        AHittable(args.material),
        center(args.center),
        radius(args.radius)
    {}
    virtual ~Sphere() {}

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
    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
    {
        rt::vector<float, 3> v = r.getOrigin() - this->center;
        float half_b = rt::dot(v, r.getDirection());
        float disc = half_b * half_b - rt::dot(v, v) + this->radius * this->radius;
        if (disc < 0)
            return (false);
        float sqrt_disc = sqrt(disc);
        if (-half_b + sqrt_disc < t_min)
            return (false);
        if (-half_b - sqrt_disc < t_min)
            rec.t = -half_b + sqrt_disc;
        else
            rec.t = -half_b - sqrt_disc;
        rec.p = r.getPointAt(rec.t);
        rec.normal = (rec.p - this->center).normalize();
        this->setHitRecordMaterial(rec);
        return (true);
    }
};

#endif
