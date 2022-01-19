/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:19 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 03:46:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AHITTABLE_HPP
# define AHITTABLE_HPP

#include "HitRecord.hpp"
#include "Ray.hpp"

struct HitRecord;

struct Material
{
    rt::vector<float, 3> color;
	float   shininess;
	float	ambient;
	float	diffusion;
	float	specular;
	float	mirror;
	float	wrinkle;

    Material();
};

class AHittable
{
private:
    Material _material;

public:
    // non copyable
    AHittable(const AHittable& rhs);
    AHittable& operator=(const AHittable& rhs);
    
    AHittable(const Material& material);
    
    virtual ~AHittable();

    virtual bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const = 0;

    Material getMaterial() const;

    void setHitRecordMaterial(HitRecord& rec) const;
};


#endif
