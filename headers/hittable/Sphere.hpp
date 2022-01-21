/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:39 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:33:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_HPP
# define SPHERE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct SphereArgs
{
    vec3f center;
    float radius;
    Material material;
};

class Sphere : public AHittable
{
private:
    vec3f _center;
    float _radius;

    // non copyable
    Sphere(const Sphere& rhs);
    Sphere& operator=(const Sphere& rhs);

public:
    Sphere(const SphereArgs& args);
    virtual ~Sphere() {}
    bool hit(const Ray3f& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
