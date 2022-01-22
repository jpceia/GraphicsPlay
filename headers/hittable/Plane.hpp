/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:57:15 by jpceia           ###   ########.fr       */
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
    vec3f _point;
    vec3f _normal;

    // non copyable
    Plane(const Plane& rhs);
    Plane& operator=(const Plane& rhs);

public:
    Plane(const PlaneArgs& args);
    virtual ~Plane() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
