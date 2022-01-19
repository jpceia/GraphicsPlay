/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/18 06:05:07 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_HPP
# define CONE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct ConeArgs
{
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
    float radius;
    float height;
    Material material;
};

class Cone : public AHittable
{
private:
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
	float	radius;
	float	height;

    // non copyable
    Cone(const Cone& rhs) : AHittable(rhs.getMaterial()) {}
    Cone& operator=(const Cone& rhs) { (void)rhs; return *this; }
public:
    Cone(const ConeArgs& args) :
        AHittable(args.material),
        p(args.p),
        direction(args.direction),
        radius(args.radius),
        height(args.height)
    {
    }
    
    virtual ~Cone() {}

    /*
     * Checks if a ray hits a cone
     * The equation of a cone is:
     * 	|(p - p0) x n)| = R * (1 - <p-p0, n> / H)
     * 	<p - p0, n> \in [0, height]
     * Substituting p by our ray r(t) = r0 + t * d, t > 0
     * We have a 2nd degree equation "a * t^2 + b * t + c = 0" 
     * with coeficients
     * a = |d x n|^2 - (R/H * <d,n>)^2
     * b = 2 * <d x n, v x n> + 2 * <d,n> * (H - <v,n>) * (R/H)^2
     * c = |v x n|^2 - (R - <v,n>/H)^2
     * where v = r0 - p0
     * 
     * The solution is t = -h +- sqrt(h^2 - c)
     * with h = b / (2 * a)
     * 
     * Regarding the height of the cone, we still have
     * <r(t) - p0, n> = <d * t + v, n> = t * <d,n> + <v, n> between 0 and H
     * with v = r0 - p0
     */
    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const
    {
        rt::vector<float, 3>    v = r.getOrigin() - this->p;
        rt::vector<float, 3>    d_cross_n = rt::cross(r.getDirection(), this->direction);
        rt::vector<float, 3>    v_cross_n = rt::cross(v, this->direction);
        float			        v_dot_n = rt::dot(v, this->direction);
        float			        d_dot_n = rt::dot(r.getDirection(), this->direction);

        float tmp1 = d_dot_n * this->radius / this->height;
        float tmp2 = d_dot_n * (this->height - v_dot_n);
        float tmp3 = (this->height - v_dot_n) * this->radius / this->height;
	    float a = d_cross_n.lengthSquared() - tmp1 * tmp1;
        float b = 2 * (rt::dot(d_cross_n, v_cross_n) + tmp2 * tmp2);
        float c = v_cross_n.lengthSquared() - tmp3 * tmp3;

        
        float   disc = b * b - 4 * a * c;
        if (disc < 0)
            return (false);
        float sqrt_disc = std::sqrt(disc);
        float t1 = (-b - sqrt_disc) / (2 * a);
        float t2 = (-b + sqrt_disc) / (2 * a);
        if (t2 < t_min || t1 > t_max)
            return (false);
        float	t = -1.0;
        if (t2 < t1)
            return (false);
        if (t1 >= t_min)
        {
            float h = v_dot_n + t1 * d_dot_n;
            if (h >= 0 && h <= this->height)
                t = t1;
        }
        if (t != t1)
        {
            float h = v_dot_n + t * d_dot_n;
            if (h < 0 || h > this->height)
                return (false);
        }
        
        /*
        * Normal vector to cone
        * https://math.stackexchange.com/questions/3349384/
        * normal-vector-of-a-cone-pointing-outward
        */
        if (t < 0)
            return false;
        rec.t = t;
        rec.p = r.getPointAt(t);
        rec.normal = rec.p - this->p;
        float alpha = rt::dot(rec.normal, this->direction);
        alpha *= std::pow(this->radius / this->height, 2) - 1;
        rec.normal += this->direction * alpha;
        rec.normal = rec.normal.normalize();
        this->setHitRecordMaterial(rec);
        return (true);
    }
};

#endif
