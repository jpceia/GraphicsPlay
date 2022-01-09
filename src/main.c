/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:37:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_args		args;
	t_data		*vars;

	if (argc != 3)
	{
		ft_putendl_error("usage: ./miniRT [scene_file] [output_file]");
		return (EXIT_FAILURE);
	}
	args.width = WIN_WIDTH;
	args.height = WIN_HEIGHT;
	args.title = "MiniRT";
	args.scene_fname = argv[1];
	args.output_fname = argv[2];
	args.n_reflections = 3;
	args.n_antialias = 1;
	vars = ft_calloc(1, sizeof(t_data));
	if (!vars)
		clean_exit(NULL, MALLOC_ERR, NULL, 1);
	data_init(vars, &args);
	data_draw_image(vars);
	data_clean(vars);
	return (EXIT_SUCCESS);
}
