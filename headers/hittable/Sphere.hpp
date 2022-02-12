/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:39 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 14:36:45 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_HPP
# define SPHERE_HPP

# include "AHittable.hpp"

struct SphereArgs
{
    vec3f center;
    float radius;
    Material material;
};

class Sphere : public AHittable
{
private:
    const vec3f _center;
    const float _radius_sq;

    // non-assignable
    Sphere& operator=(const Sphere& rhs);

public:
    Sphere(const SphereArgs& args);
    Sphere(const Sphere& rhs);
    virtual ~Sphere() {}
    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
