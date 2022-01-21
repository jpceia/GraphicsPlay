/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:31:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:22:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "AHittable.hpp"
# include "HitRecord.hpp"
# include "Vector.hpp"
# include "Ray.hpp"

struct TriangleArgs
{
    vec3f vertex[3];
    Material material;
};

class Triangle : public AHittable
{
private:
    vec3f _vertex[3];

    // non copyable
    Triangle(const Triangle& rhs);
    Triangle& operator=(const Triangle& rhs);

public:
    Triangle(const TriangleArgs& args);
    virtual ~Triangle() {}
    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
