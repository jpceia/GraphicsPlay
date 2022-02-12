/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 14:44:44 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_HPP
# define CONE_HPP

# include "AHittable.hpp"

struct ConeArgs
{
    vec3f base;
    vec3f direction;
    float radius;
    float height;
    Material material;
};

class Cone : public AHittable
{
private:
    const vec3f _base;
    const vec3f _direction;
	const float _height;
    const float _radius_height_sq;

    // non-assignable
    Cone& operator=(const Cone& rhs);

    bool _valid_hit(float t, float dot_base, float dot_direction) const;

    vec3f _get_normal(const vec3f& p) const;
    
public:
    Cone(const Cone& rhs);
    Cone(const ConeArgs& args);
    
    virtual ~Cone() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
