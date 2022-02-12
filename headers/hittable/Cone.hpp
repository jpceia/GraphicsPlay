/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 10:20:23 by jpceia           ###   ########.fr       */
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
    vec3f _base;
    vec3f _direction;
	float _radius;
	float _height;

    // non-assignable
    Cone& operator=(const Cone& rhs);

    bool _valid_hit(float t, float dot_base, float dot_direction) const;
    
public:
    Cone(const Cone& rhs);
    Cone(const ConeArgs& args);
    
    virtual ~Cone() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
