/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:29:44 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 00:49:03 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_HPP
# define LIGHT_HPP

#include "Vector.hpp"
#include "miniRT.h"

struct  LightArgs
{
    rt::vector<float, 3>	origin; // position
    rt::vector<float, 3>    color;
    float			        ratio; // intensity
};

class Light
{
	rt::vector<float, 3> 	origin;
	float	ratio;
	rt::vector<float, 3>	color;

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
    rt::vector<float, 3> getOrigin() const { return this->origin; }
    float getRatio() const { return this->ratio; }
    rt::vector<float, 3> getColor() const { return this->color; }
};

#endif