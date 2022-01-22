/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:29:44 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:19:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_HPP
# define LIGHT_HPP

#include "Vector.hpp"

struct  LightArgs
{
    vec3f	origin; // position
    vec3f    color;
    float			        ratio; // intensity
};

class Light
{
	vec3f 	origin;
	float	ratio;
	vec3f	color;

    Light() {}

public:
    // Constructors
    Light(const LightArgs& args) :
        origin(args.origin),
        ratio(args.ratio),
        color(args.color)
    {
    }

    Light(const Light& rhs) :
        origin(rhs.origin),
        ratio(rhs.ratio),
        color(rhs.color)
    {
    }

    Light& operator=(const Light& rhs)
    {
        this->origin = rhs.origin;
        this->ratio = rhs.ratio;
        this->color = rhs.color;
        return *this;
    }

    // Destructor
    
    virtual ~Light() {}

    // Getters
    vec3f getOrigin() const { return this->origin; }
    float getRatio() const { return this->ratio; }
    vec3f getColor() const { return this->color; }
};

#endif