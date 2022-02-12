/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:31:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:24:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "AHittable.hpp"

struct TriangleArgs
{
    vec3f vertex[3];
    Material material;
};

class Triangle : public AHittable
{
private:
    const vec3f _base;
    const vec3f _coedge1;
    const vec3f _coedge2;
    const vec3f _normal;

    // non copyable
    Triangle(const Triangle& rhs);
    Triangle& operator=(const Triangle& rhs);

public:
    Triangle(const TriangleArgs& args);
    virtual ~Triangle() {}
    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
