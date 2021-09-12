/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 15:21:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include <mlx.h>

int	win_close(int keycode, t_data *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_scenario	scenario;
	t_rgb		*buf;
	t_data		vars;

	if (argc != 2)
	{
		ft_putendl("Please provide only one argument");
		exit(EXIT_FAILURE);
	}
	scenario_init(&scenario);
	parse_scenario_from_file(&scenario, argv[1]);
	buf = (t_rgb *)malloc(WIN_WIDTH * WIN_HEIGHT * sizeof(*buf));
	calculate_camera_list_params(scenario.cameras, WIN_WIDTH, WIN_HEIGHT);
	raytrace_scenario(&scenario, buf);
	vars.mlx = mlx_init();
	vars.width = WIN_WIDTH;
	vars.height = WIN_HEIGHT;
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "42 - MiniRT");
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	image_from_matrix(&vars, buf);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, win_close, &vars);
	mlx_loop(vars.mlx);
	clear_scenario(&scenario);
	free(buf);
	return (EXIT_SUCCESS);
}
