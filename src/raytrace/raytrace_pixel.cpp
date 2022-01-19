/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_pixel.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:07:42 by jceia             #+#    #+#             */
/*   Updated: 2022/01/19 00:08:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	convert_scale(float x, float view_size, float screen_size)
{
	return (view_size * (x / screen_size - 0.5));
}

t_rgb	raytrace_pixel_contribution(const rt::vector<int, 2>& p, const Scenario& scenario)
{
	float x, y;

	x = convert_scale(p[0], scenario.getViewWidth(), scenario.getScreenWidth());
	y = convert_scale(p[1], scenario.getViewHeight(), scenario.getScreenHeight());
	rt::vector<float, 3> v; // multiply cam basis by (arr[0], arr[1], 1)
	v[0] = scenario.getCamera()->getRight()[0] * x + scenario.getCamera()->getUp()[0] * y + scenario.getCamera()->getDirection()[0];
	v[1] = scenario.getCamera()->getRight()[1] * x + scenario.getCamera()->getUp()[1] * y + scenario.getCamera()->getDirection()[1];
	v[2] = scenario.getCamera()->getRight()[2] * x + scenario.getCamera()->getUp()[2] * y + scenario.getCamera()->getDirection()[2];
	rt::Ray<float, 3> ray(scenario.getCameraPosition(), v);
	return (raytrace_single(ray, scenario, 3));
}

t_rgb	raytrace_pixel(int i, int j, int n, Scenario& scenario)
{
	t_rgb	color;
	rt::vector<int, 2>	p;

	for (int k = 0; k < n; ++k)
	{
		p[0] = (float)j + ((0.5 + k) / n);
		for (int l = 0; l < n; ++l)
		{
			p[1] = (float)i + ((0.5 + l) / n);
			color += raytrace_pixel_contribution(p, scenario);
		}
	}
	color /= (n * n);
	return (color);
}
