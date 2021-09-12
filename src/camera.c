/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 07:47:21 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 15:20:46 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>

void	calculate_camera_params(t_camera *cam, int win_width, int win_height)
{
	t_vec3D	up_vec;

	cam->direction = vec3D_normalize(cam->direction);
	if (cam->direction.y == 1.0)
		up_vec = vec3D_create(0.0, 0.0, 1.0);
	else
		up_vec = vec3D_create(0.0, 1.0, 0.0);
	cam->basis_x = vec3D_cross_product(cam->direction, up_vec);
	cam->basis_y = vec3D_cross_product(cam->direction, cam->basis_x);
	cam->pixels_width = win_width;
	cam->pixels_height = win_height;
	cam->view_width = 2 * tan(M_PI * cam->fov / 180);
	cam->view_height = win_height * cam->view_width / win_width;
}

void	calculate_camera_list_params(t_list *cam_list,
			int win_width, int win_height)
{
	while (cam_list)
	{
		calculate_camera_params(cam_list->content, win_width, win_height);
		cam_list = cam_list->next;
	}
}
