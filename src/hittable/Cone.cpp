/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:11:44 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 14:48:50 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/Cone.hpp"


Cone::Cone(const ConeArgs& args) :
    AHittable("Cone", args.material),
    _base(args.base),
    _direction(args.direction),
    _height(args.height),
    _radius_height_sq((args.radius * args.radius) / (args.height * args.height))
{
}

Cone::Cone(const Cone& rhs) :
    AHittable(rhs.getName(), rhs.getMaterial()),
    _base(rhs._base),
    _direction(rhs._direction),
    _height(rhs._height),
    _radius_height_sq(rhs._radius_height_sq)
{   
}

Cone& Cone::operator=(const Cone& rhs)
{
    (void)rhs;
    return *this;
}

bool Cone::_valid_hit(float t, float dot_base, float dot_direction) const
{
    float h = dot_base + t * dot_direction;
    return (h >= 0.0f && h <= _height);
}

vec3f Cone::_get_normal(const vec3f& p) const
{
    vec3f n = _base - p;
    float alpha = rt::dot(n, _direction) * (_radius_height_sq - 1);
    return n + _direction * alpha;
}

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
 * 
 * https://math.stackexchange.com/questions/3349384/
 */
bool Cone::hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const
{
    vec3f v = ray.getOrigin() - _base;
    vec3f d_cross_n = rt::cross(ray.getDirection(), _direction);
    vec3f v_cross_n = rt::cross(v, _direction);
    float v_dot_n = rt::dot(v, _direction);
    float d_dot_n = rt::dot(ray.getDirection(), _direction);

    Deg2eqParams params;
    float h = _height - v_dot_n;
    params.a = d_cross_n.lengthSquared() - d_dot_n * d_dot_n * _radius_height_sq;
    params.b = 2 * rt::dot(d_cross_n, v_cross_n) + 2 * d_dot_n * h * _radius_height_sq;
    params.c = v_cross_n.lengthSquared() - h * h * _radius_height_sq;

    Range rng;
    if (!deg2eq_solve(params, &rng))
        return false;
    if (rng.min > t_rng.max || rng.max < t_rng.min)
        return false;
    if (rng.min >= t_rng.min && _valid_hit(rng.min, v_dot_n, d_dot_n))
        rec.t = rng.min;
    else if (rng.max <= t_rng.max && _valid_hit(rng.max, v_dot_n, d_dot_n))
        rec.t = rng.max;
    else
        return false;
    rec.p = ray.getPointAt(rec.t);
    rec.normal = _get_normal(rec.p).normalize();;
    return true;
}
