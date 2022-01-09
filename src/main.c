/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:06:28 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>
#include <mlx.h>

int	main(int argc, char **argv)
{
	t_args		args;
	t_data		*vars;

	if (argc != 2)
	{
		ft_putendl_error("Please provide only one argument");
		exit(EXIT_FAILURE);
	}
	args.width = WIN_WIDTH;
	args.height = WIN_HEIGHT;
	args.title = "42 - MiniRT Bonus";
	args.fname = argv[1];
	args.n_reflections = 3;
	args.n_antialias = 3;
	vars = ft_calloc(1, sizeof(t_data));
	if (!vars)
		clean_exit(NULL, MALLOC_ERR, NULL, 1);
	mlx_data_init(vars, &args);
	mlx_data_update_image(vars);
	mlx_hook(vars->win, KEY_PRESS, M_KEY_PRESS, key_press, vars);
	mlx_hook(vars->win, DESTROY_NOTIFY, M_NO_EVENT, exit_handle, vars);
	mlx_loop(vars->mlx);
	return (EXIT_SUCCESS);
}
