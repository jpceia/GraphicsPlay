/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2022/01/19 04:49:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <iostream>
# include <string>
# include <sstream>
# include "Vector.hpp"
# include "Ray.hpp"
# include "Scenario.hpp"
# include "HitRecord.hpp"
# include "hittable/AHittable.hpp"
# include "hittable/Sphere.hpp"
# include "hittable/Plane.hpp"
# include "hittable/Triangle.hpp"
# include "hittable/Cone.hpp"
# include "hittable/Cylinder.hpp"
# include "hittable/Disk.hpp"
# include "Light.hpp"
# include "Camera.hpp"

class Scenario;
class Light;
struct AmbientLight;


# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define BRIGHTNESS_RATIO	2

/*
 * Parser
 */
void 		update_scenario_from_file(Scenario& scenario, const std::string& fname);
void		parse_data_item_from_line(Scenario& scenario, const std::string& line);
t_rgb		parse_rgb(std::stringstream& ss);
Material	parse_material(std::stringstream& ss);

AmbientLight parse_ambient_light(std::stringstream& ss);
Camera*		parse_camera(std::stringstream& ss);
Light		parse_light(std::stringstream& ss);


AHittable*	parse_hittable(const std::string& type, std::stringstream& ss);
Sphere*		parse_sphere(std::stringstream& ss);
Plane*		parse_plane(std::stringstream& ss);
Cylinder*	parse_cylinder(std::stringstream& ss);
Triangle*	parse_triangle(std::stringstream& ss);
Disk*		parse_disk(std::stringstream& ss);
Cone*		parse_cone(std::stringstream& ss);


/*
 * UTILS
 */

void 		create_bmp(const std::string& fname, int width, int height, t_rgb *pixels);

rt::vector<float, 3>	vec3d_random(void);

#endif
