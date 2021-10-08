/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 04:00:14 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 04:22:36 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_press(int keycode, t_data *vars)
{
	if (keycode == K_ESC)
	{
        clean_mlx_data(vars);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	exit_handle(t_data *vars)
{
	clean_mlx_data(vars);
	exit(EXIT_SUCCESS);
}
