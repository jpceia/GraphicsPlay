/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:19 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 00:06:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AHITTABLE_HPP
# define AHITTABLE_HPP

#include "HitRecord.hpp"
#include "Ray.hpp"

struct Material
{
    rt::vector<float, 3> color;
	float   shininess;
	float	ambient;
	float	diffusion;
	float	specular;
	float	mirror;
	float	wrinkle;

    Material() :
        shininess(0.0f),
        ambient(1.0f),
        diffusion(0.0f),
        specular(0.0f),
        mirror(0.0f),
        wrinkle(0.0f)
    {
    }
};

class AHittable
{
private:
    Material _material;

public:
    // non copyable
    AHittable(const AHittable& rhs) : _material(rhs.getMaterial()) {}
    AHittable& operator=(const AHittable& rhs) { (void)rhs; return *this; }
    
    AHittable(const Material& material) : _material(material) {}
    
    virtual ~AHittable() {}    

    virtual bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const = 0;

    Material getMaterial() const { return this->_material; }

    void setHitRecordMaterial(HitRecord& rec) const
    {
        rec.color = this->_material.color;
    }
};


#endif
