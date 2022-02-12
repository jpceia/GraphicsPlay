/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:29:37 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 10:54:29 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CYLINDER_HPP
# define CYLINDER_HPP

# include "AHittable.hpp"

//struct Range;

struct CylinderArgs
{
    vec3f base;
    vec3f direction;
    float radius;
    float height;
    Material material;
};

class Cylinder : public AHittable
{
private:
    vec3f _base;
    vec3f _direction;
    float _radius;
    float _height;

    // non copyable
    Cylinder(const Cylinder& rhs);
    Cylinder& operator=(const Cylinder& rhs);

    bool _valid_hit(float t, float dot_base, float dot_direction) const;

public:
    Cylinder(const CylinderArgs& args);
    
    virtual ~Cylinder() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

# endif