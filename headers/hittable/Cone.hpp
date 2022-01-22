/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:15:10 by jpceia           ###   ########.fr       */
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

    // non copyable
    Cone(const Cone& rhs);
    Cone& operator=(const Cone& rhs);
public:
    Cone(const ConeArgs& args);
    
    virtual ~Cone() {}

    bool hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const;
};

#endif
