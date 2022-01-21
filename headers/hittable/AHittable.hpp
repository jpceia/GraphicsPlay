/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:19 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 12:18:40 by jpceia           ###   ########.fr       */
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
	float	ambient;
	float	diffusion;
	float	specular;
	float   shininess;
	float	mirror;
	float	wrinkle;

    Material();
};

class AHittable
{
private:
    std::string _name;
    Material _material;

public:
    // non copyable
    AHittable(const AHittable& rhs);
    AHittable& operator=(const AHittable& rhs);
    
    AHittable(const std::string& _name, const Material& material);
    
    virtual ~AHittable();

    virtual bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const = 0;

    Material getMaterial() const;

    std::string getName() const;
};


#endif
