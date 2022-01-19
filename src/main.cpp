/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/19 03:41:54 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <iostream>

int	main(int argc, char **argv)
{
	ScenarioArgs	args;

	if (argc != 3)
	{
		std::cerr << "Usage: ./miniRT <input_file> <output_file>" << std::endl;
		return (EXIT_FAILURE);
	}
	args.width = 1920;
	args.height = 1080;
	args.title = "MiniRT";
	args.n_reflections = 3;
	args.n_antialias = 1;
	Scenario scenario(args);
	update_scenario_from_file(scenario, argv[1]); // parse scenario
	scenario.draw(argv[2]);
	return (EXIT_SUCCESS);
}
