/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:29:37 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:16:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CYLINDER_HPP
# define CYLINDER_HPP

# include "AHittable.hpp"
# include "Vector.hpp"

struct CylinderArgs
{
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
    float radius;
    float height;
    Material material;
};

class Cylinder : public AHittable
{
private:
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
    float radius;
    float height;

    // non copyable
    Cylinder(const Cylinder& rhs);
    Cylinder& operator=(const Cylinder& rhs);
public:
    Cylinder(const CylinderArgs& args);
    
    virtual ~Cylinder() {}

    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

# endif