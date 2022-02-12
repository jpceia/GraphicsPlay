/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:29:44 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:05:49 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_HPP
# define LIGHT_HPP

#include "Vector.hpp"

struct  LightArgs
{
    vec3f position;
    float intensity;
    vec3f color;
};

class Light
{
	vec3f _position;
	float _intensity;
	vec3f _color;

    Light() {}

public:
    // Constructors
    Light(const LightArgs& args) :
        _position(args.position),
        _intensity(args.intensity),
        _color(args.color)
    {
    }

    Light(const Light& rhs) :
        _position(rhs._position),
        _intensity(rhs._intensity),
        _color(rhs._color)
    {
    }

    Light& operator=(const Light& rhs)
    {
        _position = rhs._position;
        _intensity = rhs._intensity;
        _color = rhs._color;
        return *this;
    }

    // Destructor
    
    virtual ~Light() {}

    // Getters
    vec3f getPosition() const { return _position; }
    float getIntensity() const { return _intensity; }
    vec3f getColor() const { return _color; }
};

#endif
