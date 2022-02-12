/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2022/02/12 15:48:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <iostream>
# include <string>
# include <sstream>
# include "hittable/AHittable.hpp"
# include "hittable/Sphere.hpp"
# include "hittable/Plane.hpp"
# include "hittable/Triangle.hpp"
# include "hittable/Cone.hpp"
# include "hittable/Cylinder.hpp"
# include "hittable/Disk.hpp"
# include "hittable/Parallelogram.hpp"
# include "Scenario.hpp"


# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define BRIGHTNESS_RATIO	2.0

/*
 * Parser
 */
void 		update_scenario_from_file(Scenario& scenario, const std::string& fname);
void		parse_data_item_from_line(Scenario& scenario, const std::string& line);
vec3f		parse_rgb(std::stringstream& ss);
Material	parse_material(std::stringstream& ss);

AmbientLight parse_ambient_light(std::stringstream& ss);
Camera		parse_camera(std::stringstream& ss);
Light		parse_light(std::stringstream& ss);


AHittable*	parse_hittable(const std::string& type, std::stringstream& ss);
Sphere*		parse_sphere(std::stringstream& ss);
Plane*		parse_plane(std::stringstream& ss);
Cylinder*	parse_cylinder(std::stringstream& ss);
Triangle*	parse_triangle(std::stringstream& ss);
Disk*		parse_disk(std::stringstream& ss);
Cone*		parse_cone(std::stringstream& ss);
Parallelogram*	parse_parallelogram(std::stringstream& ss);


/*
 * UTILS
 */

void 		create_bmp(const std::string& fname, int width, int height, vec3f *pixels);

vec3f	vec3d_random(void);

#endif
