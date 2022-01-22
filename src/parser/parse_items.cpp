/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/22 03:37:07 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Scenario.hpp"

AmbientLight	parse_ambient_light(std::stringstream &ss)
{
	AmbientLight amb;

	ss >> amb.ratio;
	amb.color = parse_rgb(ss);
	return amb;
}

Camera parse_camera(std::stringstream &ss)
{
	CameraArgs args;
	ss >> args.origin >> args.direction >> args.fov;
	return Camera(args);
}

Light parse_light(std::stringstream& ss)
{
	LightArgs args;
	ss >> args.origin >> args.ratio;
	if (!ss.eof())
		args.color = parse_rgb(ss);
	return Light(args);
}