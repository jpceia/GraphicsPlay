/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hittables.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:26:46 by jceia             #+#    #+#             */
/*   Updated: 2022/01/21 16:24:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "miniRT.h"
#include "hittable/AHittable.hpp"
#include "hittable/Cone.hpp"
#include "hittable/Cylinder.hpp"
#include "hittable/Disk.hpp"
#include "hittable/Plane.hpp"
#include "hittable/Sphere.hpp"
#include "hittable/Triangle.hpp"


AHittable *parse_hittable(const std::string& type, std::stringstream& ss)
{
	if (type == "sp")
		return (parse_sphere(ss));
	else if (type == "pl")
		return (parse_plane(ss));
	else if (type == "cy")
		return (parse_cylinder(ss));
	else if (type == "tr")
		return (parse_triangle(ss));
	else if (type == "di")
		return (parse_disk(ss));
	else if (type == "co")
		return (parse_cone(ss));
	else
		throw std::runtime_error("Unknown object type: " + type);
}

Cone	*parse_cone(std::stringstream& ss)
{
	ConeArgs args;

	ss >> args.base >> args.direction >> args.radius >> args.height;
	args.direction = args.direction.normalize();
	args.material = parse_material(ss);
	return (new Cone(args));
}

Cylinder	*parse_cylinder(std::stringstream& ss)
{
	CylinderArgs	args;

	ss >> args.base >> args.direction >> args.radius >> args.height;
	args.material = parse_material(ss);
	args.direction = args.direction.normalize();
	return (new Cylinder(args));
}

Disk	*parse_disk(std::stringstream& ss)
{
	DiskArgs	args;

	ss >> args.center >> args.normal >> args.radius;
	args.material = parse_material(ss);
	return (new Disk(args));
}

Plane	*parse_plane(std::stringstream& ss)
{
	PlaneArgs args;

	ss >> args.p >> args.normal;
	args.normal = args.normal.normalize();
	args.material = parse_material(ss);
	return (new Plane(args));
}

Sphere	*parse_sphere(std::stringstream& ss)
{
	SphereArgs	args;

	ss >> args.center >> args.radius;
	args.material = parse_material(ss);
	return (new Sphere(args));
}

Triangle	*parse_triangle(std::stringstream& ss)
{
	TriangleArgs	args;

	ss >> args.vertex[0] >> args.vertex[1] >> args.vertex[2];
	args.material = parse_material(ss);
	return (new Triangle(args));
}
