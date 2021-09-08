/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:54:17 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 14:41:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"


/*
 * Color Interpolation
 */
t_color color_interp(t_color c1, t_color c2, float t)
{
    t_color color;
    color.t = (1 - t) * c1.t + t * c2.t;
    color.r = (1 - t) * c1.r + t * c2.r;
    color.g = (1 - t) * c1.g + t * c2.g;
    color.b = (1 - t) * c1.b + t * c2.b;
    return (color);
}

t_color color_create(float t, float r, float g, float b)
{
    t_color color;
    color.t = t;
    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}