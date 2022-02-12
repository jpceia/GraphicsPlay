/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:11:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_HPP
# define PLANE_HPP

# include "AHittable.hpp"

struct PlaneArgs
{
    vec3f point;
    vec3f normal;
    Material material;
};

class Plane : public AHittable
{
private:
    const vec3f _point;
    const vec3f _normal;

    // non-assignable
    Plane& operator=(const Plane& rhs);

public:
    Plane(const Plane& rhs);
    Plane(const PlaneArgs& args);
    virtual ~Plane() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
