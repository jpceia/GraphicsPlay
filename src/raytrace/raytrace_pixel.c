/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:07:42 by jceia             #+#    #+#             */
/*   Updated: 2021/10/22 23:12:53 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

float	convert_scale(float x, float view_size, float screen_size)
{
	return (view_size * (x / screen_size - 0.5));
}

t_rgb	raytrace_pixel_contribution(const t_vec2d *p, const t_data *vars)
{
	t_camera	*cam;
	t_ray3d		ray;
	t_vec3d		v;

	cam = vars->camera;
	v = vec3d_create(
			convert_scale(p->x, cam->view_width, cam->pixels_width),
			-convert_scale(p->y, cam->view_height, cam->pixels_height),
			1);
	ray = ray3d_create(cam->origin, matrix_mul_vec3d(cam->basis, &v));
	return (raytrace_single_bonus(&ray, vars, vars->n_reflections));
}

t_rgb	raytrace_pixel(int i, int j, int n, t_data *vars)
{
	int		k;
	int		l;
	t_rgb	color;
	t_vec2d	p;

	color = vec3d_origin();
	k = 0;
	while (k < n)
	{
		l = 0;
		p.x = (float)j + ((0.5 + k) / n);
		while (l < n)
		{
			p.y = (float)i + ((0.5 + l) / n);
			color = vec3d_add(color, raytrace_pixel_contribution(&p, vars));
			l++;
		}
		k++;
	}
	color = vec3d_scalar_mul(color, 1 / (1.0 * n * n));
	return (color);
}
