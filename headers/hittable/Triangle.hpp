/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:31:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/18 05:54:34 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "AHittable.hpp"
# include "HitRecord.hpp"
# include "Vector.hpp"
# include "Ray.hpp"

struct TriangleArgs
{
    rt::vector<float, 3> p1;
    rt::vector<float, 3> p2;
    rt::vector<float, 3> p3;
    Material material;
};

class Triangle : public AHittable
{
private:
    rt::vector<float, 3> p1, p2, p3;

    // non copyable
    Triangle(const Triangle& rhs) : AHittable(rhs.getMaterial()) {}
    Triangle& operator=(const Triangle& rhs) { (void)rhs; return *this; }

public:
    Triangle(const TriangleArgs& args) :
        AHittable(args.material),
        p1(args.p1),
        p2(args.p2),
        p3(args.p3)
    {}
    
    virtual ~Triangle() {}

    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
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
        this->setHitRecordMaterial(rec);
        return (true);
    }
};

#endif
