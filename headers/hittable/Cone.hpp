/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:15:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_HPP
# define CONE_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct ConeArgs
{
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
    float radius;
    float height;
    Material material;
};

class Cone : public AHittable
{
private:
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
	float	radius;
	float	height;

    // non copyable
    Cone(const Cone& rhs);
    Cone& operator=(const Cone& rhs);
public:
    Cone(const ConeArgs& args);
    
    virtual ~Cone() {}

    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
