/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:22:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_HPP
# define PLANE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct PlaneArgs
{
    vec3f p;
    vec3f normal;
    Material material;
};

class Plane : public AHittable
{
private:
    vec3f p;
    vec3f _normal;

    // non copyable
    Plane(const Plane& rhs);
    Plane& operator=(const Plane& rhs);

public:
    Plane(const PlaneArgs& args);
    virtual ~Plane() {}

    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
