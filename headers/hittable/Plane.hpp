/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/18 05:59:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_HPP
# define PLANE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct PlaneArgs
{
    rt::vector<float, 3> p;
    rt::vector<float, 3> normal;
    Material material;
};

class Plane : public AHittable
{
private:
    rt::vector<float, 3> p;
    rt::vector<float, 3> n;

    // non copyable
    Plane(const Plane& rhs) : AHittable(rhs.getMaterial()) {}
    Plane& operator=(const Plane& rhs) { (void)rhs; return *this; }

public:
    Plane(const PlaneArgs& args) :
        AHittable(args.material),
        p(args.p),
        n(args.normal)
    {}
    virtual ~Plane() {}

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
    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
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
        this->setHitRecordMaterial(rec);
        return (true);
    }
};

#endif
