/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 15:52:34 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_scenario	scenario;

	if (argc != 2)
	{
		ft_putendl("Please provide only one argument");
		exit(EXIT_FAILURE);
	}
	scenario_init(&scenario);
	parse_scenario_from_file(&scenario, argv[1]);
	clear_scenario(&scenario);
	return (EXIT_SUCCESS);
}
