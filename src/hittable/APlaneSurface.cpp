/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APlaneSurface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:11:35 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/APlaneSurface.hpp"

APlaneSurface::APlaneSurface(const APlaneSurface& rhs) :
    AHittable(rhs),
    _base(rhs._base),
    _normal(rhs._normal)
{
}

APlaneSurface::APlaneSurface(
    const std::string& name,
    const Material& mat,
    const vec3f &base,
    const vec3f &normal) :
    AHittable(name, mat),
    _base(base),
    _normal(normal)
{
}

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
bool APlaneSurface::hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const
{
    float dot_prod = rt::dot(ray.getDirection(), _normal);
    if (dot_prod == 0)
        return false;
    rec.t = -rt::dot(ray.getOrigin() - _base, _normal) / dot_prod;
    if (!t_rng.contains(rec.t))
        return false;
    rec.p = ray.getPointAt(rec.t);
    if (!_check_boundary(rec.p))
        return false;
    rec.normal = _normal;
    return true;
}
