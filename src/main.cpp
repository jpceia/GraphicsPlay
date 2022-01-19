/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/18 06:52:37 by jpceia           ###   ########.fr       */
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
	args.width = WIN_WIDTH;
	args.height = WIN_HEIGHT;
	args.title = "MiniRT";
	args.scene_fname = argv[1];
	args.output_fname = argv[2];
	args.n_reflections = 3;
	args.n_antialias = 1;
	Scenario scenario(args);
	update_scenario_from_file(scenario, args.scene_fname);
	scenario.setupCamera();
	raytrace_scenario(scenario);
	create_bmp(scenario.getFileName(), scenario.getScreenWidth(), scenario.getScreenHeight(), scenario.getPixels());
	return (EXIT_SUCCESS);
}
