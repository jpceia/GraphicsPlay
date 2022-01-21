/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:39 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:07:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_HPP
# define SPHERE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct SphereArgs
{
    rt::vector<float, 3>	center;
    float					radius;
    Material                material;
};

class Sphere : public AHittable
{
private:
    rt::vector<float, 3> center;
    float radius;

    // non copyable
    Sphere(const Sphere& rhs);
    Sphere& operator=(const Sphere& rhs);

public:
    Sphere(const SphereArgs& args);
    virtual ~Sphere() {}
    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
