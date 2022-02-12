/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/22 03:54:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	ScenarioArgs	args;

	if (argc != 3)
	{
		std::cerr << "Usage: ./miniRT <input_file> <output_file>" << std::endl;
		return (EXIT_FAILURE);
	}
	args.width = 1080;
	args.height = 720;
	args.title = "ray tracer";
	args.n_reflections = 3;
	args.n_antialias = 2;
	Scenario scenario(args);
	update_scenario_from_file(scenario, argv[1]); // parse scenario
	scenario.draw(argv[2]);
	return (EXIT_SUCCESS);
}
