/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 02:32:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 09:42:29 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/AHittable.hpp"

Material::Material() :
    ambient(1.0f),
    diffusion(1.0f),
    specular(0.0f),
    shininess(0.0f),
    mirror(0.0f),
    wrinkle(0.0f)
{
}

AHittable::AHittable(const AHittable& rhs) :
    _name(rhs._name),
    _material(rhs._material)
{
}

AHittable& AHittable::operator=(const AHittable& rhs)
{
    (void)rhs;
    //_name = rhs.getName();
    //_material = rhs.getMaterial();
    return *this;
}
    
AHittable::AHittable(const std::string &name, const Material& material) :
    _name(name),
    _material(material)
{
}
    
AHittable::~AHittable()
{
}

Material AHittable::getMaterial() const
{
    return _material;
}

std::string AHittable::getName() const
{
    return _name;
}
