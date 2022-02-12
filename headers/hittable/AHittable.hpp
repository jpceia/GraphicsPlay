/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:19 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 09:41:45 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AHITTABLE_HPP
# define AHITTABLE_HPP

# include "Vector.hpp"
# include "Range.hpp"
# include "Ray.hpp"

//struct Range;
//struct HitRecord;

class AHittable;

struct HitRecord
{
	vec3f   	p;
	vec3f    	normal;
	vec3f    	reflected;
    AHittable*	hittable;
	float		t;
};


struct Material
{
    vec3f   color;
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
    const std::string _name;
    const Material _material;

    // Non-assignable
    AHittable& operator=(const AHittable& rhs);

public:
    AHittable(const AHittable& rhs);
    AHittable(const std::string& _name, const Material& material);
    
    virtual ~AHittable();

    virtual bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const = 0;

    Material getMaterial() const;

    std::string getName() const;
};


#endif
