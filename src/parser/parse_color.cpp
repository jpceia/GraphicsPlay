/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:05:04 by jceia             #+#    #+#             */
/*   Updated: 2022/01/21 16:23:00 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hittable/AHittable.hpp"
#include <sstream>

vec3f	parse_rgb(std::stringstream& ss)
{
	vec3f	rgb;

	ss >> rgb;
	rgb /= 255.0f;
	return (rgb);
}

Material parse_material(std::stringstream& ss)
{
	Material	material;
	material.color = parse_rgb(ss);
	float *refs[6] = {
		&material.ambient,
		&material.diffusion,
		&material.specular,
		&material.shininess,
		&material.mirror, // reflection
		&material.wrinkle
	};
	for (std::size_t i=0; i<6; ++i)
	{
		if (ss.eof())
			break;
		if (ss.fail())
			throw std::runtime_error("parse_material: invalid line");
		ss >> *refs[i];
	}
	return material;
}
