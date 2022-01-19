/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_items.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/18 07:21:05 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Scenario.hpp"

AmbientLight	parse_ambient_light(std::stringstream &ss)
{
	AmbientLight amb;

	ss >> amb.color;
	ss >> amb.ratio;
	return amb;
}

Camera *parse_camera(std::stringstream &ss)
{
	CameraArgs args;
	ss >> args.origin >> args.direction >> args.fov;
	return new Camera(args);
}

Light parse_light(std::stringstream& ss)
{
	LightArgs args;
	ss >> args.origin >> args.ratio;
	if (!ss.eof())
		ss >> args.color;
	return Light(args);
}