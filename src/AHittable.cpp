/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHittable.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 02:32:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 02:33:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable/AHittable.hpp"

Material::Material() :
    shininess(0.0f),
    ambient(1.0f),
    diffusion(0.0f),
    specular(0.0f),
    mirror(0.0f),
    wrinkle(0.0f)
{
}

AHittable::AHittable(const AHittable& rhs) : _material(rhs.getMaterial()) {}
AHittable& AHittable::operator=(const AHittable& rhs) { (void)rhs; return *this; }
    
AHittable::AHittable(const Material& material) : _material(material) {}
    
AHittable::~AHittable() {}

Material AHittable::getMaterial() const { return this->_material; }

void AHittable::setHitRecordMaterial(HitRecord& rec) const
{
    rec.color = _material.color;
}