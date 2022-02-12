/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:29:47 by jceia             #+#    #+#             */
/*   Updated: 2022/02/12 12:29:44 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <fstream>
#include "Scenario.hpp"
#include "miniRT.hpp"

void	parse_data_item_from_line(Scenario& scenario, const std::string& line)
{
	std::stringstream	ss(line);
	std::string			type;

	ss >> type;
	if (type == "#") // comment
		return ;
	if (type == "A")
		scenario.setAmbientLight(parse_ambient_light(ss));	
	else if (type == "C")
		scenario.setCamera(parse_camera(ss));
	else if (type == "l")
		scenario.addLight(parse_light(ss));
	else
		scenario.addHittable(parse_hittable(type, ss));
}

void update_scenario_from_file(Scenario& scenario, const std::string& fname)
{
	// check the file extension - needs to be .rt
	if (fname.substr(fname.find_last_of(".")) != ".rt")
		throw std::runtime_error("Unexpected file extension");
	// open the file
	std::ifstream file(fname.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error opening file");
	// read the file
	std::string	line;
	while (std::getline(file, line))
		parse_data_item_from_line(scenario, line); // parse the line
	// close the file
	file.close();
}